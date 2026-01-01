/* count lines, words, and characters in input */
#include <stdio.h>

#define IB 3     // inbetween two words
#define STR 2    // start of line
#define IN 1     // inside a word
#define OUT 0    // outside a word
#define MAX_WORD_LEN 5000
int main(void)
{
  int state, c;
  int word_lens[MAX_WORD_LEN + 1]; // value at index - count of words of length index
  state = STR;
  int c_num = 0;

  // Initialize array
  for ( int i = 1; i <= MAX_WORD_LEN; i++ ) word_lens[i] = 0;

  // Get count for each length of word found
  while((c = getchar()) != EOF)
    {
      if     ( state == STR ) {
        if      ( c == '\n' )             { state = STR; c_num = 1; }
        else if ( c == ' ' || c == '\t' ) { state = OUT; c_num = 1; }
        else                              { state = IN; c_num = 1;  }
      }
      else if ( state == IN ) {
        if      ( c == '\n' )             { state = STR; ++word_lens[c_num]; }
        else if ( c == ' ' || c == '\t' ) { state = IB;  ++word_lens[c_num]; }
        else                              { state = IN;  ++c_num; }
      }
      else if (state == OUT ) {
        if      ( c == '\n' )             { state = STR;  c_num = 1; }
        else if ( c == ' ' || c == '\t' ) { state = OUT; c_num = 1; }
        else                              { state = IN; c_num = 1; }
      }
      else if (state == IB ) {
        if      ( c == '\n' )             { state = STR;c_num = 1; }
        else if ( c == ' ' || c == '\t' ) { state = IB; c_num = 1; }
        else                              { state = IN; c_num = 1; }
      }
      else {
        printf("INVALID STATE");
      }
    }

  // Print histogram
  for ( int word_len = 1; word_len <= MAX_WORD_LEN; word_len++ ) {
    int word_len_count = word_lens[word_len];
    if ( word_len_count > 0 ) {
      printf("%d: ", word_len);
      for ( int c_num = 0; c_num < word_lens[word_len]; c_num++ ) {
        putchar('x');
      }
      putchar('\n');
    }
  }
  return 0;
}
