#include <stdio.h>

float fahrToCels(float fahr);

int main(void)
{
  int fahr;

  for (fahr = 0; fahr <= 300; fahr += 20)
    printf("%3d %6.1f\n", fahr, fahrToCels(fahr));

  return 0;
}

float fahrToCels(float fahr) { return (5.0/9.0)*(fahr-32); }
