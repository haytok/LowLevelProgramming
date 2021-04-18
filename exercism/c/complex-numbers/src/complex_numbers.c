#include "complex_numbers.h"

complex_t c_add(complex_t a, complex_t b)
{
   complex_t c = (complex_t) {
      .real = a.real + b.real,
      .imag = a.imag + b.imag,
   };
   return c;
}

complex_t c_sub(complex_t a, complex_t b)
{
   complex_t c = (complex_t) {
      .real = a.real - b.real,
      .imag = a.imag - b.imag,
   };
   return c;
}

complex_t c_mul(complex_t a, complex_t b)
{
   complex_t c = (complex_t) {
      .real = a.real * b.real - a.imag * b.imag,
      .imag = a.real * b.imag + b.real * a.imag,
   };
   return c;
}

complex_t c_div(complex_t a, complex_t b)
{
   double value = pow(b.real, 2) + pow(b.imag, 2);
   complex_t c = (complex_t) {
      .real = (a.real * b.real + a.imag * b.imag) / value,
      .imag = (a.imag * b.real - a.real * b.imag) / value,
   };
   return c;
}

double c_abs(complex_t x)
{
   return sqrt(pow(x.real, 2) + pow(x.imag, 2));
}

complex_t c_conjugate(complex_t x)
{
   x.imag *= -1;
   return x;
}

double c_real(complex_t x)
{
   return x.real;
}

double c_imag(complex_t x)
{
   return x.imag;
}

complex_t c_exp(complex_t x)
{
   complex_t c = (complex_t){
       .real = exp(x.real),
       .imag = 0.0,
   };
   if (x.imag != 0.0) {
      c.real *= (double)cos(x.imag);
      c.imag *= (double)sin(x.imag);
   }
   return c;
}
