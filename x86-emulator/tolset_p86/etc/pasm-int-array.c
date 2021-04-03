void func(void) {
  int arr[4], i;
  int *x = &arr[0];
  x[0] = 1
  arr[1] = 2
  *(x + 2) = 3;
  *(arr + 3) = 4;
  /* arr : {1, 2, 3, 4} */
}
