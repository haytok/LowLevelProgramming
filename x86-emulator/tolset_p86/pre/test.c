#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"
#include "modrm.h"

#ifdef COLORED
#define ESC(e) "\x1b[" e "m"
#else
#define ESC(e) ""
#endif

#define assert(expr) \
    do { \
        if (!(expr)) { \
            sprintf(assert_msg, "'%s' %s:%d", #expr, __FILE__, __LINE__); \
            return; \
        } else { \
            assert_msg[0] = '\0'; \
        } \
    } while (0)

#define RUN(f) run_test(f, #f, assert_msg)
static char assert_msg[1024];
static int failed_cases = 0, total_cases = 0;
static void run_test(void (*f)(void), const char* fname, const char* assert_msg)
{
    fprintf(stderr, "========\nRunning %s\n", fname);
    total_cases++;
    f();
    if (assert_msg[0] == '\0') {
        fprintf(stderr, ESC("32") "SUCCESS" ESC("0") "\n");
    } else {
        fprintf(stderr, ESC("31") "FAILED" ESC("0") ": %s\n", assert_msg);
        failed_cases++;
    }
    fprintf(stderr, "\n");
}
static void print_result(void)
{
    fprintf(stderr, "Tested %d cases.", total_cases);
    if (failed_cases > 0) {
        fprintf(stderr, ESC("31") "  %d failed." ESC("0") "\n", failed_cases);
    } else {
        fprintf(stderr, ESC("32") "  All succeeded." ESC("0") "\n");
    }
}

#define CF (1u << 0)
#define ZF (1u << 6)
#define SF (1u << 7)
#define OF (1u << 11)

uint8_t emu_buf[sizeof(Emulator) + 1024 * 1024];
static Emulator* init_emu()
{
    Emulator* emu = (Emulator*)emu_buf;
    emu->memory = emu_buf + sizeof(Emulator);
    memset(emu->memory, 0, sizeof(emu_buf) - sizeof(Emulator));
    memset(emu->registers, 0, sizeof(uint32_t) * REGISTERS_COUNT);
    emu->eip = 0x7c00;
    emu->registers[ESP] = 0x7c00;
    emu->int_index = -1;
    return emu;
}

void test_basic_functions(void)
{
    Emulator* emu = init_emu();

    emu->memory[0] = 0x78;
    emu->memory[1] = 0x56;
    emu->memory[2] = 0x34;
    emu->memory[3] = 0x12;
    assert(get_memory32(emu, 0) == 0x12345678);

    set_memory32(emu, 4, 0x11223344);
    assert(emu->memory[4] == 0x44);
    assert(emu->memory[5] == 0x33);
    assert(emu->memory[6] == 0x22);
    assert(emu->memory[7] == 0x11);

    set_register32(emu, ECX, 0x12345678);
    assert(emu->registers[ECX] == 0x12345678);
    assert(get_register32(emu, ECX) == 0x12345678);

    set_register8(emu, ECX, 0xa5); // cl
    assert(get_register8(emu, ECX) == 0xa5);
    assert(get_register32(emu, ECX) == 0x123456a5);

    set_register8(emu, ECX + 4, 0x29); // ch
    assert(get_register8(emu, ECX + 4) == 0x29);
    assert(get_register32(emu, ECX) == 0x123429a5);
}

void test_parse_modrm(void)
{
    ModRM modrm;
    Emulator* emu;
    uint32_t eip0;

    emu = init_emu();
    eip0 = emu->eip;
    memcpy(emu->memory + emu->eip, "\x45\xfc", 2);
    parse_modrm(emu, &modrm);

    assert(modrm.mod == 1);
    assert(modrm.reg_index == 0);
    assert(modrm.rm == 5);
    assert(modrm.sib == 0);
    assert(modrm.disp8 == -4);
    assert(emu->eip == eip0 + 2);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x9c\x8b\x00\x02\x00\x00", 6);
    parse_modrm(emu, &modrm);

    assert(modrm.mod == 2);
    assert(modrm.reg_index == 3);
    assert(modrm.rm == 4);
    assert(modrm.sib == 0x8b); // [4 * ecx + ebx]
    assert(modrm.disp32 == 512);
    assert(emu->eip == eip0 + 6);
}

void test_set_rm8(void)
{
    Emulator* emu;
    ModRM modrm;

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x02", 1);
    emu->registers[EDX] = 0x104;
    parse_modrm(emu, &modrm);
    set_rm8(emu, &modrm, 0x5a);

    assert(get_memory32(emu, 0x104) == 0x0000005a);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x45\xfc", 2);
    emu->registers[EBP] = 0x104;
    parse_modrm(emu, &modrm);
    set_rm8(emu, &modrm, 0x29);

    assert(get_memory32(emu, 0x100) == 0x00000029);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xbe\x00\x02\x00\x00", 5);
    emu->registers[ESI] = 0x0600;
    parse_modrm(emu, &modrm);
    set_rm8(emu, &modrm, 0xfc);

    assert(get_memory32(emu, 0x0800) == 0x000000fc);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xc1", 1); // cl
    parse_modrm(emu, &modrm);
    emu->registers[ECX] = 0x12345678;
    set_rm8(emu, &modrm, 0xf8);

    assert(emu->registers[ECX] == 0x123456f8);
    assert(emu->registers[EBP] == 0);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xc5", 1); // ch
    parse_modrm(emu, &modrm);
    emu->registers[ECX] = 0x12345678;
    set_rm8(emu, &modrm, 0x11);

    assert(emu->registers[ECX] == 0x12341178);
    assert(emu->registers[EBP] == 0);
}

void test_set_rm32(void)
{
    Emulator* emu;
    ModRM modrm;

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x30", 1);
    emu->registers[EAX] = 0x104;
    parse_modrm(emu, &modrm);
    set_rm32(emu, &modrm, 0x11223344);

    assert(get_memory32(emu, 0x104) == 0x11223344);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x45\xfc", 2);
    emu->registers[EBP] = 0x104;
    parse_modrm(emu, &modrm);
    set_rm32(emu, &modrm, 0x11223344);

    assert(get_memory32(emu, 0x100) == 0x11223344);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xbe\x00\x02\x00\x00", 5);
    emu->registers[ESI] = 0x0600;
    parse_modrm(emu, &modrm);
    set_rm32(emu, &modrm, 0x11223344);

    assert(get_memory32(emu, 0x0800) == 0x11223344);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xc1", 1);
    parse_modrm(emu, &modrm);
    set_rm32(emu, &modrm, 0x11223344);

    assert(emu->registers[ECX] == 0x11223344);

    /* not implemented
    emu = init_emu();
    // SIB: [4 * ECX + ESI + disp8(+0x10)]
    memcpy(emu->memory + emu->eip, "\x44\x8e\x10", 3);
    emu->registers[ESI] = 0x0100;
    emu->registers[ECX] = 3;
    parse_modrm(emu, &modrm);
    set_rm32(emu, &modrm, 0x11223344);

    assert(get_memory32(emu, 0x011c) == 0x11223344);
    */
}

void test_get_rm8(void)
{
    Emulator* emu;
    ModRM modrm;

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x05\xfc\x00\x01\x00", 5);
    set_memory32(emu, 0x000100fc, 0x12345678);
    parse_modrm(emu, &modrm);

    assert(get_rm8(emu, &modrm) == 0x78);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x45\xfc", 2);
    emu->registers[EBP] = 0x0104;
    set_memory32(emu, 0x100, 0x12345678);
    parse_modrm(emu, &modrm);

    assert(get_rm8(emu, &modrm) == 0x78);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x8b\x10\x01\x00\x00", 5);
    emu->registers[EBX] = 0x0100;
    set_memory32(emu, 0x0210, 0x12345678);
    parse_modrm(emu, &modrm);

    assert(get_rm8(emu, &modrm) == 0x78);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xc0", 1); // al
    emu->registers[EAX] = 0x12345678;
    parse_modrm(emu, &modrm);

    assert(get_rm8(emu, &modrm) == 0x78);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xc4", 1); // ah
    emu->registers[ESP] = 0x8000;
    emu->registers[EAX] = 0x12345678;
    parse_modrm(emu, &modrm);

    assert(get_rm8(emu, &modrm) == 0x56);
    assert(emu->registers[ESP] == 0x8000);
}

void test_get_rm32(void)
{
    Emulator* emu;
    ModRM modrm;

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x05\xfc\x00\x01\x00", 5);
    set_memory32(emu, 0x000100fc, 0x12345678);
    parse_modrm(emu, &modrm);

    assert(get_rm32(emu, &modrm) == 0x12345678);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x45\xfc", 2);
    emu->registers[EBP] = 0x0104;
    set_memory32(emu, 0x100, 0x12345678);
    parse_modrm(emu, &modrm);

    assert(get_rm32(emu, &modrm) == 0x12345678);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x8b\x10\x01\x00\x00", 5);
    emu->registers[EBX] = 0x0100;
    set_memory32(emu, 0x0210, 0x12345678);
    parse_modrm(emu, &modrm);

    assert(get_rm32(emu, &modrm) == 0x12345678);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\xc4", 1);
    emu->registers[ESP] = 0x8000;
    parse_modrm(emu, &modrm);

    assert(get_rm32(emu, &modrm) == 0x8000);
}

void test_set_r8(void)
{
    Emulator* emu;
    ModRM modrm;

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x08", 1); // cl
    emu->registers[ECX] = 0x11223344;
    parse_modrm(emu, &modrm);
    set_r8(emu, &modrm, 0xa5);

    assert(emu->registers[ECX] == 0x112233a5);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x3f", 1); // bh
    emu->registers[EDI] = 0x12345678;
    emu->registers[EBX] = 0x11223344;
    parse_modrm(emu, &modrm);
    set_r8(emu, &modrm, 0x01);

    assert(emu->registers[EDI] == 0x12345678);
    assert(emu->registers[EBX] == 0x11220144);
}

void test_get_r8(void)
{
    Emulator* emu;
    ModRM modrm;

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x08", 1); // cl
    emu->registers[ECX] = 0x11223344;
    parse_modrm(emu, &modrm);

    assert(get_r8(emu, &modrm) == 0x44);

    emu = init_emu();
    memcpy(emu->memory + emu->eip, "\x3f", 1); // bh
    emu->registers[EDI] = 0x12345678;
    emu->registers[EBX] = 0x11223344;
    parse_modrm(emu, &modrm);

    assert(get_r8(emu, &modrm) == 0x33);
}

void test_01(void)
{
    Emulator* emu;

    emu = init_emu();

    // add [ebp-4], eax
    memcpy(emu->memory + emu->eip, "\x01\x45\xfc", 3);
    set_memory32(emu, 0x100, 2);
    emu->registers[EBP] = 0x104;
    emu->registers[EAX] = 5;

    instructions[0x01](emu);

    assert(get_memory32(emu, 0x100) == 7);
    assert((emu->eflags & CF) == 0);
    assert((emu->eflags & ZF) == 0);
    assert((emu->eflags & SF) == 0);
    assert((emu->eflags & OF) == 0);
    assert(emu->eip == 0x7c03);

    emu = init_emu();

    // add [ebp-4], eax
    memcpy(emu->memory + emu->eip, "\x01\x45\xfc", 3);
    set_memory32(emu, 0x100, 0x1fffffff);
    emu->registers[EBP] = 0x104;
    emu->registers[EAX] = 0xe0000001;

    instructions[0x01](emu);

    assert(get_memory32(emu, 0x100) == 0);
    assert((emu->eflags & CF) != 0);
    assert((emu->eflags & ZF) != 0);
    assert((emu->eflags & SF) == 0);
    assert((emu->eflags & OF) == 0);
    assert(emu->eip == 0x7c03);
}

void test_3b(void)
{
    Emulator* emu = init_emu();

// macro for "cmp eax, [ebp]". calc "a - b" then test "CF=c, ZF=z, SF=s, OF=o".
#define TEST_CMP(a, b, c, z, s, o) \
    do { \
        emu = init_emu(); \
        memcpy(emu->memory + emu->eip, "\x3b\x45\x00", 3); \
        emu->registers[EAX] = (a); \
        emu->registers[EBP] = 0x100; \
        set_memory32(emu, 0x100, (b)); \
        instructions[0x3b](emu); \
        assert(((emu->eflags & CF) != 0) == (c)); \
        assert(((emu->eflags & ZF) != 0) == (z)); \
        assert(((emu->eflags & SF) != 0) == (s)); \
        assert(((emu->eflags & OF) != 0) == (o)); \
        assert(emu->eip == 0x7c03); \
    } while (0)

    TEST_CMP(5, 4, 0, 0, 0, 0);
    TEST_CMP(5, 5, 0, 1, 0, 0);
    TEST_CMP(5, 6, 1, 0, 1, 0);
    TEST_CMP(-3, -2, 1, 0, 1, 0);
    TEST_CMP(-3, -3, 0, 1, 0, 0);
    TEST_CMP(-3, -4, 0, 0, 0, 0);

#undef TEST_CMP
}

void test_3c(void)
{
    Emulator* emu = init_emu();

// macro for "cmp al, imm8". calc "a - b" then test "CF=c, ZF=z, SF=s, OF=o".
#define TEST_CMP(a, b, c, z, s, o) \
    do { \
        emu = init_emu(); \
        emu->memory[emu->eip + 0] = 0x3c; \
        emu->memory[emu->eip + 1] = (b); \
        emu->registers[EAX] = (a); \
        instructions[0x3c](emu); \
        assert(((emu->eflags & CF) != 0) == (c)); \
        assert(((emu->eflags & ZF) != 0) == (z)); \
        assert(((emu->eflags & SF) != 0) == (s)); \
        assert(((emu->eflags & OF) != 0) == (o)); \
        assert(emu->eip == 0x7c02); \
    } while (0)

    TEST_CMP(5, 4, 0, 0, 0, 0);
    TEST_CMP(5, 5, 0, 1, 0, 0);
    TEST_CMP(5, 6, 1, 0, 1, 0);
    TEST_CMP(-3, -2, 1, 0, 1, 0);
    TEST_CMP(-3, -3, 0, 1, 0, 0);
    TEST_CMP(-3, -4, 0, 0, 0, 0);

#undef TEST_CMP
}

void test_3d(void)
{
    Emulator* emu = init_emu();

// macro for "cmp eax, imm32". calc "a - b" then test "CF=c, ZF=z, SF=s, OF=o".
#define TEST_CMP(a, b, c, z, s, o) \
    do { \
        emu = init_emu(); \
        emu->memory[emu->eip + 0] = 0x3d; \
        set_memory32(emu, emu->eip + 1, (int32_t)(b)); \
        emu->registers[EAX] = (int32_t)(a); \
        instructions[0x3d](emu); \
        assert(((emu->eflags & CF) != 0) == (c)); \
        assert(((emu->eflags & ZF) != 0) == (z)); \
        assert(((emu->eflags & SF) != 0) == (s)); \
        assert(((emu->eflags & OF) != 0) == (o)); \
        assert(emu->eip == 0x7c05); \
    } while (0)

    TEST_CMP(5, 4, 0, 0, 0, 0);
    TEST_CMP(5, 5, 0, 1, 0, 0);
    TEST_CMP(5, 6, 1, 0, 1, 0);
    TEST_CMP(-3, -2, 1, 0, 1, 0);
    TEST_CMP(-3, -3, 0, 1, 0, 0);
    TEST_CMP(-3, -4, 0, 0, 0, 0);

#undef TEST_CMP
}

void test_41(void)
{
    Emulator* emu = init_emu();

    // inc ecx
    memcpy(emu->memory + emu->eip, "\x41", 1);
    emu->registers[ECX] = 41;

    instructions[0x41](emu);

    assert(emu->registers[ECX] == 42);
    assert(emu->eip == 0x7c01);
}

void test_54(void)
{
    Emulator* emu = init_emu();

    // push esp
    memcpy(emu->memory + emu->eip, "\x54", 1);
    emu->registers[ESP] = 0x7c00;

    instructions[0x54](emu);

    assert(get_memory32(emu, 0x7bfc) == 0x7c00);
    assert(emu->registers[ESP] == 0x7bfc);
    assert(emu->eip == 0x7c01);
}

void test_5d(void)
{
    Emulator* emu = init_emu();

    // pop ebp
    memcpy(emu->memory + emu->eip, "\x5d", 1);
    emu->registers[ESP] = 0x0600;
    set_memory32(emu, 0x0600, 0x12345678);

    instructions[0x5d](emu);

    assert(emu->registers[EBP] == 0x12345678);
    assert(emu->registers[ESP] == 0x0604);
    assert(emu->eip == 0x7c01);
}

void test_68(void)
{
    Emulator* emu = init_emu();

    // push dword 0x12345678
    memcpy(emu->memory + emu->eip, "\x68\x78\x56\x34\x12", 5);
    emu->registers[ESP] = 0x7c00;

    instructions[0x68](emu);

    assert(get_memory32(emu, 0x7bfc) == 0x12345678);
    assert(emu->registers[ESP] == 0x7bfc);
    assert(emu->eip == 0x7c05);
}

void test_6a(void)
{
    Emulator* emu = init_emu();

    // push byte 41
    memcpy(emu->memory + emu->eip, "\x68\x29", 2);
    emu->registers[ESP] = 0x7c00;

    instructions[0x6A](emu);

    assert(get_memory32(emu, 0x7bfc) == 41);
    assert(emu->registers[ESP] == 0x7bfc);
    assert(emu->eip == 0x7c02);
}

void test_78(void)
{
    Emulator* emu = init_emu();

    // js (offset -9)
    memcpy(emu->memory + emu->eip, "\x78\xf7", 2);
    emu->eflags = SF;

    instructions[0x78](emu);

    assert(emu->eip == 0x7c02 - 9);
}

void test_7c(void)
{
    Emulator* emu = init_emu();

    // jl (offset -11)
    memcpy(emu->memory + emu->eip, "\x7c\xf5", 2);
    emu->eflags = 0;

    instructions[0x7c](emu);

    assert(emu->eip == 0x7c02);

    emu = init_emu();

    // jl (offset -11)
    memcpy(emu->memory + emu->eip, "\x7c\xf5", 2);
    emu->eflags = OF;

    instructions[0x7c](emu);

    assert(emu->eip == 0x7c02 - 11);

    emu = init_emu();

    // jl (offset -11)
    memcpy(emu->memory + emu->eip, "\x7c\xf5", 2);
    emu->eflags = SF;

    instructions[0x7c](emu);

    assert(emu->eip == 0x7c02 - 11);

    emu = init_emu();

    // jl (offset -11)
    memcpy(emu->memory + emu->eip, "\x7c\xf5", 2);
    emu->eflags = SF | OF;

    instructions[0x7c](emu);

    assert(emu->eip == 0x7c02);
}

void test_7e(void)
{
    Emulator* emu = init_emu();

    // jng (offset -13)
    memcpy(emu->memory + emu->eip, "\x78\xf3", 2);
    emu->eflags = ZF;

    instructions[0x7e](emu);

    assert(emu->eip == 0x7c02 - 13);
}

void test_83(void)
{
    Emulator* emu;

    emu = init_emu();

    // add esp, byte 8
    memcpy(emu->memory + emu->eip, "\x83\xc4\x08", 3);
    emu->registers[ESP] = 0x7bf0;

    instructions[0x83](emu);

    assert(emu->registers[ESP] == 0x7bf8);
    assert(emu->eip == 0x7c03);

    emu = init_emu();

    // sub dword [ebp+4], byte 41
    memcpy(emu->memory + emu->eip, "\x83\x6d\x04\x29", 4);
    emu->registers[EBP] = 0x100;
    set_memory32(emu, 0x104, 0xffffff2a);

    instructions[0x83](emu);

    assert(get_memory32(emu, 0x104) == 0xffffff01);
    assert((emu->eflags & CF) == 0);
    assert((emu->eflags & ZF) == 0);
    assert((emu->eflags & SF) != 0);
    assert((emu->eflags & OF) == 0);
    assert(emu->eip == 0x7c04);

    emu = init_emu();

    // sub dword [eax], byte 41
    memcpy(emu->memory + emu->eip, "\x83\x28\x29", 3);
    emu->registers[EAX] = 0x100;
    set_memory32(emu, 0x100, 41);

    instructions[0x83](emu);

    assert(get_memory32(emu, 0x100) == 0);
    assert((emu->eflags & CF) == 0);
    assert((emu->eflags & ZF) != 0);
    assert((emu->eflags & SF) == 0);
    assert((emu->eflags & OF) == 0);
    assert(emu->eip == 0x7c03);

    emu = init_emu();

// macro for "cmp dword [esi], byte X". calc "a - b" then test "CF=c, ZF=z, SF=s, OF=o".
#define TEST_CMP(a, b, c, z, s, o) \
    do { \
        emu = init_emu(); \
        memcpy(emu->memory + emu->eip, "\x83\x3e", 2); \
        emu->memory[emu->eip + 2] = (b); \
        emu->registers[ESI] = 0x100; \
        set_memory32(emu, 0x100, (a)); \
        instructions[0x83](emu); \
        assert(((emu->eflags & CF) != 0) == (c)); \
        assert(((emu->eflags & ZF) != 0) == (z)); \
        assert(((emu->eflags & SF) != 0) == (s)); \
        assert(((emu->eflags & OF) != 0) == (o)); \
        assert(emu->eip == 0x7c03); \
    } while (0)

    TEST_CMP(5, 4, 0, 0, 0, 0);
    TEST_CMP(5, 5, 0, 1, 0, 0);
    TEST_CMP(5, 6, 1, 0, 1, 0);
    TEST_CMP(-3, -2, 1, 0, 1, 0);
    TEST_CMP(-3, -3, 0, 1, 0, 0);
    TEST_CMP(-3, -4, 0, 0, 0, 0);
    TEST_CMP(0xfffffff0, 0xff, 1, 0, 1, 0);

#undef TEST_CMP
}

void test_88(void)
{
    Emulator* emu = init_emu();

    // mov [ebp-4], cl
    memcpy(emu->memory + emu->eip, "\x88\x4d\xfc", 3);
    emu->registers[EBP] = 0x104;
    emu->registers[ECX] = 0x12345678;

    instructions[0x88](emu);

    assert(get_memory8(emu, 0x100) == 0x78);
    assert(emu->eip == 0x7c03);
}

void test_89(void)
{
    Emulator* emu = init_emu();

    // mov [ebp-4], ebx
    memcpy(emu->memory + emu->eip, "\x89\x5d\xfc", 3);
    emu->registers[EBP] = 0x104;
    emu->registers[EBX] = 0x12345678;

    instructions[0x89](emu);

    assert(get_memory32(emu, 0x100) == 0x12345678);
    assert(emu->eip == 0x7c03);
}

void test_8a(void)
{
    Emulator* emu = init_emu();

    // mov bh, [ebp+4]
    memcpy(emu->memory + emu->eip, "\x8a\x7d\x04", 3);
    emu->registers[EBP] = 0x100;
    emu->registers[EBX] = 0x12345678;
    set_memory8(emu, 0x104, 0xfa);

    instructions[0x8a](emu);

    assert(emu->registers[EBX] == 0x1234fa78);
    assert(emu->eip == 0x7c03);
}

void test_8b(void)
{
    Emulator* emu = init_emu();

    // mov eax, [ebp]
    memcpy(emu->memory + emu->eip, "\x8b\x45\x00", 3);
    emu->registers[EBP] = 0x100;
    set_memory32(emu, 0x100, 41);

    instructions[0x8b](emu);

    assert(emu->registers[EAX] == 41);
    assert(emu->eip == 0x7c03);

    /* not implemented
    emu = init_emu();

    // mov edi, [ecx]
    memcpy(emu->memory + emu->eip, "\x8b\x39", 2);
    emu->registers[ECX] = 0xfffc;
    set_memory32(emu, 0xfffc, 12);

    instructions[0x8b](emu);

    assert(emu->registers[EDI] == 12);
    assert(emu->eip == 0x7c02);
    */
}

void test_8d(void)
{
    Emulator* emu = init_emu();

    // lea eax, [ebp-4]
    memcpy(emu->memory + emu->eip, "\x8d\x45\xfc", 3);
    emu->registers[EBP] = 0x7bfc;

    instructions[0x8d](emu);

    assert(emu->registers[EAX] == 0x7bf8);
    assert(emu->eip == 0x7c03);
}

void test_99(void)
{
    Emulator* emu = init_emu();

    // cwd
    memcpy(emu->memory + emu->eip, "\x99", 1);
    emu->registers[EAX] = 0xffffffd7; // -41

    instructions[0x99](emu);

    assert(emu->registers[EAX] == 0xffffffd7);
    assert(emu->registers[EDX] == 0xffffffff);
    assert(emu->eip == 0x7c01);
}

void test_a1(void)
{
    Emulator* emu = init_emu();

    // mov eax, [0x7c4e]
    memcpy(emu->memory + emu->eip, "\xa1\x4e\x7c\x00\x00", 5);
    set_memory32(emu, 0x7c4e, 0x12345678);

    instructions[0xa1](emu);

    assert(emu->registers[EAX] == 0x12345678);
    assert(emu->eip == 0x7c05);
}

void test_a3(void)
{
    Emulator* emu = init_emu();

    // mov [0x7c4e], eax
    memcpy(emu->memory + emu->eip, "\xa3\x4e\x7c\x00\x00", 5);
    emu->registers[EAX] = 0x12345678;

    instructions[0xa3](emu);

    assert(get_memory32(emu, 0x7c4e) == 0x12345678);
    assert(emu->eip == 0x7c05);
}

void test_b4(void)
{
    Emulator* emu = init_emu();

    // mov ah, 0x60
    memcpy(emu->memory + emu->eip, "\xb4\x60", 2);
    emu->registers[EAX] = 0x11111111;

    instructions[0xb4](emu);

    assert(emu->registers[EAX] == 0x11116011);
    assert(emu->eip == 0x7c02);
}

void test_bc(void)
{
    Emulator* emu = init_emu();

    // mov esp, 0x0600
    memcpy(emu->memory + emu->eip, "\xbc\x00\x06\x00\x00", 5);

    instructions[0xbc](emu);

    assert(emu->registers[ESP] == 0x0600);
    assert(emu->eip == 0x7c05);
}

void test_c3(void)
{
    Emulator* emu = init_emu();

    // ret
    memcpy(emu->memory + emu->eip, "\xc3", 1);
    emu->registers[ESP] = 0x7bfc;
    set_memory32(emu, 0x7bfc, 0x0600);

    instructions[0xc3](emu);

    assert(emu->registers[ESP] == 0x7c00);
    assert(emu->eip == 0x0600);
}

void test_c7(void)
{
    Emulator* emu = init_emu();

    // mov dword [ebp+20], 0x04030201
    memcpy(emu->memory + emu->eip, "\xc7\x45\x20\x01\x02\x03\x04", 7);
    emu->registers[EBP] = 0x100;

    instructions[0xc7](emu);

    assert(get_memory32(emu, 0x120) == 0x04030201);
    assert(emu->eip == 0x7c07);
}

void test_c9(void)
{
    Emulator* emu = init_emu();

    // leave (set esp to ebp, then pop ebp)
    memcpy(emu->memory + emu->eip, "\xc9", 1);
    emu->registers[ESP] = 0x7b00;
    emu->registers[EBP] = 0x7bf8;
    set_memory32(emu, 0x7bf8, 0x12345678);

    instructions[0xc9](emu);

    assert(emu->registers[ESP] == 0x7bfc);
    assert(emu->registers[EBP] == 0x12345678);
    assert(emu->eip == 0x7c01);
}

void test_e8(void)
{
    Emulator* emu = init_emu();

    // call (offset +12)
    memcpy(emu->memory + emu->eip, "\xe8\x0c\x00\x00\x00", 5);
    emu->registers[ESP] = 0x0600;

    instructions[0xe8](emu);

    assert(emu->registers[ESP] == 0x05fc);
    assert(get_memory32(emu, emu->registers[ESP]) == 0x7c05);
    assert(emu->eip == 0x7c05 + 12);
}

void test_e9(void)
{
    Emulator* emu = init_emu();

    // jmp near (offset +8)
    memcpy(emu->memory + emu->eip, "\xe9\x08\x00\x00\x00", 5);

    instructions[0xe9](emu);

    assert(emu->eip == 0x7c05 + 8);
}

void test_eb(void)
{
    Emulator* emu = init_emu();

    // jmp near (offset +6)
    memcpy(emu->memory + emu->eip, "\xeb\x06", 2);

    instructions[0xeb](emu);

    assert(emu->eip == 0x7c02 + 6);
}

void test_f7(void)
{
    Emulator* emu = init_emu();

    // idiv dword [ebp-4]
    memcpy(emu->memory + emu->eip, "\xf7\x7d\xfc", 3);
    emu->registers[EBP] = 0x104;
    emu->registers[EDX] = 0x00000001;
    emu->registers[EAX] = 0x23456789;
    set_memory32(emu, 0x100, 128);

    instructions[0xf7](emu);

    assert(emu->registers[EAX] == 38177487);
    assert(emu->registers[EDX] == 9);
    assert(emu->eip == 0x7c03);
}

void test_ff(void)
{
    Emulator* emu = init_emu();

    // inc dword [ebp-4]
    memcpy(emu->memory + emu->eip, "\xff\x45\xfc", 3);
    emu->registers[EBP] = 0x100;
    set_memory32(emu, 0xfc, 41);

    instructions[0xff](emu);

    assert(get_memory32(emu, 0xfc) == 42);
    assert(emu->eip == 0x7c03);
}

int main(void)
{
    init_instructions();

    RUN(test_basic_functions);
    RUN(test_parse_modrm);
    RUN(test_set_rm8);
    RUN(test_set_rm32);
    RUN(test_get_rm8);
    RUN(test_get_rm32);
    RUN(test_set_r8);
    RUN(test_get_r8);
    RUN(test_01);
    RUN(test_3b);
    RUN(test_3c);
    RUN(test_3d);
    RUN(test_41);
    RUN(test_54);
    RUN(test_5d);
    RUN(test_68);
    RUN(test_6a);
    RUN(test_78);
    RUN(test_7c);
    RUN(test_7e);
    RUN(test_83);
    RUN(test_88);
    RUN(test_89);
    RUN(test_8a);
    RUN(test_8b);
    RUN(test_8d);
    RUN(test_99);
    RUN(test_a1);
    RUN(test_a3);
    RUN(test_b4);
    RUN(test_bc);
    RUN(test_c3);
    RUN(test_c7);
    RUN(test_c9);
    RUN(test_e8);
    RUN(test_e9);
    RUN(test_eb);
    RUN(test_f7);
    RUN(test_ff);

    print_result();
}
