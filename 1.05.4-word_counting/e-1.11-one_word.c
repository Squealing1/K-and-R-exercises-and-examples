/* count lines, words, and characters in input */
#include <stdio.h>

#define IB 3     // inbetween two words
#define STR 2    // start of line
#define IN 1     // inside a word
#define OUT 0    // outside a word
int main(void)
{
  int state, c;
  state = STR;

  while((c = getchar()) != EOF)
    {
      if     ( state == STR ) {
        if      ( c == '\n' )             { state = STR; /* May want this: putchar('\n') */ }
        else if ( c == ' ' || c == '\t' ) { state = OUT; }
        else                              { state = IN;  putchar(c); }
      }
      else if ( state == IN ) {
        if      ( c == '\n' )             { state = STR; putchar('\n'); }
        else if ( c == ' ' || c == '\t' ) { state = IB; }
        else                              { state = IN; putchar(c); }
      }
      else if (state == OUT ) {
        if      ( c == '\n' )             { state = STR; putchar('\n'); }
        else if ( c == ' ' || c == '\t' ) { state = OUT; }
        else                              { state = IN; putchar(c); }
      }
      else if (state == IB ) {
        if      ( c == '\n' )             { state = STR; putchar('\n'); }
        else if ( c == ' ' || c == '\t' ) { state = IB; }
        else                              { state = IN; putchar('\n'); putchar(c); }
      }
      else {
        printf("INVALID STATE");
      }

      

    }

  return 0;
}
