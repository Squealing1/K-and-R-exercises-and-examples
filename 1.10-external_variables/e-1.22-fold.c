/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define WRAPWIDTH 16
#define TESTTABSTOP 8
#define TESTWRAPWIDTH 16

int getLine(char s[], int lim);
void appendString(char to[], char from[]);
int getStringLen(char s[]);
int getSubString(char sub[], char s[], int str, int end);
void stripExtraNewlines(char s[]);
void wrapLine(char line[], char append[]);
void appendChar(char to[], char from);

int main(void)
{
  char append[MAXLINE] = "";
  char append_simple[MAXLINE] = "";
  char line[MAXLINE];
  int len;
  int wrap = 0;
  while((len = getLine(line, MAXLINE)) > 0) {
    wrapLine(line, append);
  }

  return 0;
}

void wrapLine(char line[], char append[]){
    int len;
    append[0] = '\0';
    len = getStringLen(line);
    printf("len: %d\n", len);
    char wt_line[MAXLINE] = "";
    int i;
    int last_char = 0;
    int past_wrap = 0;
    for (int i = 0; i < len; i+=1) { 
      appendChar(wt_line,line[i]);
      if ( (i + 1) % WRAPWIDTH == 0 ) past_wrap = 1;
      if ( past_wrap ) {
       appendString(append,wt_line);
       appendString(append,"\n");
       past_wrap = 0;
       wt_line[0] = '\0';
      }
    }
    appendString(append, wt_line);

    stripExtraNewlines(append);


    printf("%s",append);
}

void stripExtraNewlines(char s[]){
    // Strip extra newlines
    int a_len = getStringLen(s);
    int i;
    for(i = a_len; s[i] == '\n' || s[i] == '\0'; i--) s[i] = '\0';
    s[i+1] = '\n';
    s[i+2] = '\0';
}

int getSubString(char sub[], char s[], int str, int end){
  int len = end - str + 1;
  int i;
  for( i = 0; i < len; i++) {
    sub[i] = s[i+str];
  }
  sub[i] = '\0';


  return 0;

}
int getStringLen(char s[]){
  int i;
  for (i = 0; s[i] != '\0'; i++);
  return i; // include '\0'
}

void appendChar(char to[], char from){
  int len_to = getStringLen(to);
  to[len_to] = from;
  to[len_to+1] = '\0';
}

void appendString(char to[], char from[]){
  int len_to = getStringLen(to);
  int len_from = getStringLen(from);
  for (int i = 0; i < len_from + 2 /* include \0*/; i++) to[len_to + i] = from[i];
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
