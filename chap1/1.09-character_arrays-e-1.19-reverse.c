/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000

int getLine(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[], int len);

int main(void)
{
  int len;                  // current line length
  char line[MAXLINE];       // current input line

  while ((len = getLine(line, MAXLINE)) > 0){
    reverse(line, len);
    printf("%s",line);
  }
  
  return 0;
}

/* reverse: reverse a string of characters
 * does not check if string is empty or valid. */
void reverse(char s[], int len){
  char left_c;
  for ( int left_i = 0; left_i < len/2 /* Swap accross the middle of string */; left_i++ ) {
    int right_i = (len-1)-left_i;
    // Swap characters at opposite sides of string
    left_c = s[left_i];
    s[left_i] = s[right_i];
    s[right_i] = left_c;
  }
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim)
{
  int c, i;

  for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
