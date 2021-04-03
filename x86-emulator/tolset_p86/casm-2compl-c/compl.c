#include <stdio.h>
#include <stdint.h>

int main(void) {
  int8_t s_val = -41;
  uint8_t u_val = s_val;
  printf("signed = %d (%x), unsigned = %d (%x)\n",
    s_val, s_val, u_val, u_val);
  return 0;
}
