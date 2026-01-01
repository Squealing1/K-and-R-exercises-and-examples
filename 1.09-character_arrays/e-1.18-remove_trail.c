/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000

int removeTrail(char s[], int len);
int getLine(char line[], int maxline);
void replaceNewLine(char s[], int len, char replacement);
void copy(char to[], char from[]);

int main(void)
{
  int len;                  // current line length
  char line[MAXLINE];       // current input line
  char line_s[MAXLINE]; 
  char line_p[MAXLINE];

  while ((len = getLine(line, MAXLINE)) > 0) {

    copy(line_p, line);
    int has_char = removeTrail(line, MAXLINE);
    if ( has_char == 1 ) {

      copy(line_s, line_p);
      replaceNewLine(line_s, len, '@');
      printf("PRE: %s:E\n", line_s);

      copy(line_s, line);
      replaceNewLine(line_s, len, '@');
      printf("AFT: %s:E\n", line_s);

    }

  }
  
  return 0;
}

void replaceNewLine(char s[], int len, char replacement) {
  char c;
  for ( int i = 0; i < len; i++ ){
    c = s[i];
    if ( c == '\n' ) s[i] = replacement;
  }
}

/* Return -1 - no nonblank and nontab characters
 * Return index - last nonblank and nontab character */
int lastNonBlankTab(char s[], int len){
  int last_index = -1;
  char c;
  for ( int i = 0; i < len; i++ ){
    c = s[i];
    if ( c == '\n' ) return last_index;
    if ( c != '\t' && c != ' ') last_index = i;
  }
  return last_index;
    
}

/* Remove tabs and spaces at end of line 
 * Return 0 - only tabs and spaces
 * Return 1 - Some characters that are not tabs or spaces
 * Return 2 - All characters are not tabs or spaces */
int removeTrail(char s[], int len){
  int last_index;
  last_index = lastNonBlankTab(s, len);
  if ( last_index == -1 ){ 
    s[0] = '\n';
    s[1] = '\0';
    return 0;
  }

  // Delete tabs and spaces after last_index
  if ( s[last_index+1] != '\n' ) {
    s[last_index+1] = '\n';
    s[last_index+2] = '\0';
    return 1;
  }
  else {
    return 2;
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
