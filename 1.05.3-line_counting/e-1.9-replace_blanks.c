/* count lines in input */
#include <stdio.h>

int main(void)
{
  int c, sp;

  sp = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (sp == 0) {
        putchar(c);
        ++sp;
	    }
    }
    else 
    {
      putchar(c);
      sp = 0;
    }
  }

  return 0;
}
