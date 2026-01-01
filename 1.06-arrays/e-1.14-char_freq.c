#include <stdio.h>

#define MAX_CHARS 6000


int main() {
  // initialize char_counts
  int char_counts[MAX_CHARS];
  for ( int i = 0; i < MAX_CHARS; i++) {
    char_counts[i] = 0;
  }

  int c;

  // count char frequencies
  while((c = getchar()) != EOF) {
    char_counts[c]++;
  }


  // print histogram
  for ( int ch = 0; ch < MAX_CHARS; ch++) {
    int char_count = char_counts[ch];
    if ( char_count > 0 ) {
      printf("%3d-",ch);
      if ( ch == '\n' ) printf("\\n: ");
      else {
        putchar(ch);
        printf(" : ");
      }
      for ( int char_num = 0; char_num < char_count; char_num++ ) putchar('x');
      putchar('\n');
    }
  }
    

}
