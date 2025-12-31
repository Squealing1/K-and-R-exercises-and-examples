/* count lines in input */
#include <stdio.h>

int main(void)
{
  int c, nl, t, sp;

  nl = 0;
  t = 0;
  sp = 0;
  while ((c = getchar()) != EOF)
  {
    if (c == '\n')
      ++nl;
    if (c == '\t')
      ++t;
    if (c == ' ')
      ++sp;
  }

  printf("nl: %d\n", nl);
  printf("t: %d\n", t);
  printf("sp: %d\n", sp);

  return 0;
}
