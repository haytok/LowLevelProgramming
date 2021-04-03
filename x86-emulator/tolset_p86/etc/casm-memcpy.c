void *memcpy(void *dest, const void *src, int n) {
  int i;
  for (i = 0; i < n; ++i) {
    *((char *)dest + i) = *((const char *)src + i);
  }
  return dest;
}
