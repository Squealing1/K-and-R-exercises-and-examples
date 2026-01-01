/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000


int getLine(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
  int len;                  // current line length
  int t_len;
  int max;                  // maximum length seen so far
  char line[MAXLINE];       // current input line
  char longest[MAXLINE];    // longest line saved here
  char t_line[MAXLINE];

  max = 0;
  while ((len = getLine(line, MAXLINE)) > 0) {
    t_len = len;
    while (len == MAXLINE && t_line[MAXLINE-1] != '\n' && t_line[MAXLINE-1] != EOF) {
      len = getLine(t_line, MAXLINE);
      t_len += len;
    }
    if (t_len > max)
      {
        max = t_len;
        copy(longest, line);
      }
  }
  if (max > 0) {            // there was a line
    printf("len: %d\n", max);
    printf("%s", longest);
  }
  
  return 0;
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim)
{
  int c, i;

  for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
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
