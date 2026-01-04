/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define WRAPWIDTH 16

int getLine(char line[], int maxline);
int wrapLine(char line[], char w_line[], int start_index, int wrapwidth, int tabstop);
void copy(char to[], char from[]);

void replaceNewLine(char s[], int len, char replacement) {
  char c;
  for ( int i = 0; i < len; i++ ){
    c = s[i];
    if ( c == '\n' ) s[i] = replacement;
  }
}
int main(void)
{
  int len;                  // current line length
  char line[MAXLINE];       // current input line
  char w_line[MAXLINE];
  char d_line[MAXLINE];
  while ((len = getLine(line, MAXLINE)) > 0) {
    copy(d_line, line);
    replaceNewLine(d_line, len, '|');
    printf("OOO:%s\n",d_line);
    int start_index = 0;
    int pre_start_index = -1;
    do  {
      pre_start_index = start_index;
      (start_index = wrapLine(line, w_line, start_index, WRAPWIDTH, TABSTOP));
      copy(d_line, w_line);
      replaceNewLine(d_line, len, '|');
      printf("---:%s\n",d_line);
      if ( start_index <= pre_start_index && start_index != -1 ){
        printf("ERROR: start_index: %d <= pre_start_index: %d\n", start_index, pre_start_index);
        break;
      }
    }
    while  ( start_index >= 0 );
  }

  return 0;
}

int tabcolumns(int column, int tabstop) { return tabstop - (column % tabstop); }

void cutLine(char line[], char w_line[], int start_index, int end_index){
  int i;
  for(i = 0; i < end_index - start_index; i++) {
    w_line[i] = line[start_index + i];
  }
  w_line[i] = '\n';
  w_line[i+1] = '\0';
}


/* wrapLine: Cut lines larger than wrapwidth into multiple lines less than wrapwidth 
 * return -1 - No wraps
 * return i - Wraps at i */ 
int wrapLine(char line[], char w_line[], int start_index, int wrapwidth, int tabstop) {
  int column = 0;
  int prev_ws_i = -1; // The first whitespace character before the last end of a word
  int prev_char_i = -1; // The start of the word after the wrap
  int i;


  for(i = start_index; line[ i] != '\n' && line[ i] != '\0'; i++) {
    if ( line[ i] == '\t' ) { // Tab found
       if ( prev_char_i >= prev_ws_i ) {
         prev_ws_i = i;
        }
        column += tabcolumns(column, tabstop); // Tab takes up multiple columns
    }
    else if ( line[ i] == ' ' ) { // Space found
       if ( prev_char_i >= prev_ws_i ) {
         prev_ws_i = i;
       }
       column++;
    }
    else { // Character found
       if ( prev_char_i <= prev_ws_i ) {
         prev_char_i = i;
       }
       if (column > wrapwidth && prev_ws_i != -1) break;
       column++;
      }
  }

  if ( prev_ws_i == -1 ) {
    cutLine(line, w_line, start_index, i); 
    return -1;
  }
  else {
    cutLine(line, w_line, start_index, prev_ws_i);
    return prev_char_i;
  }



}



/* getLine: read a line into s, return length
 * return i -  Line length */
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
