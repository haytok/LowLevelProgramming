#include "allergies.h"

bool is_allergic_to(allergen_t allergen, int value) {
    int *data;
    data = malloc(sizeof(int) * LENGTH);
    create_data(value, data);
    return data[allergen] == 1;
}

allergen_list_t get_allergens(int value) {
    int *data;
    data = malloc(sizeof(int) * LENGTH);
    create_data(value, data);

    allergen_list_t allergen_list;
    allergen_list.count = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (i < ALLERGEN_COUNT && data[i]) {
            allergen_list.allergens[i] = true;
            allergen_list.count++;
        }
    }

    return allergen_list;
}

void create_data(int value, int *data) {
    int n = 0;
    int bit = 1;
    int length = (int)(log10((double)value) / log10((double)2));
    while (length >= 0) {
        // 下の桁から計算
        bit = (value >> n) & 1;
        data[n] = bit;
        n++;
        length--;
    }
}
