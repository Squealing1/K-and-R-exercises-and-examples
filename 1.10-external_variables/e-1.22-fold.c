/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define WRAPWIDTH 16
#define TESTTABSTOP 8
#define TESTWRAPWIDTH 16

int get_string_length(char s[]);
void cut_string(char cut[], char from[], int str, int end);
int getLine(char line[], int maxline);
int findWrapIndex(char line[], int start_index, int wrapwidth, int tabstop);
void wrapLine(char line[],  char result_line[], int wrapwidth, int tabstop);
void copy(char to[], char from[]);
int copy_to_string(char to[], char from[], int str_to, int end_to, int str_from, int end_from);
void replaceNewLine(char s[], char replacement); 
int is_same(char to[], char from[]);
void fail_test(char fail_message[], char input_string[], char result_string[], char expected_string[]);
int tests();
int tabcolumns(int column, int tabstop) { return tabstop - (column % tabstop); }
int get_line_length(char line[]);

int main(void)
{
  int len;                  // current line length
  char line[MAXLINE];       // current input line
  char w_line[MAXLINE];
  char d_line[MAXLINE];
//  while ((len = getLine(line, MAXLINE)) > 0) {
//    copy(d_line, line);
//    replaceNewLine(d_line, len, '|');
//    int start_index = 0;
//    int pre_start_index = -1;
//    do  {
//      if ( start_index < pre_start_index && start_index != -1 ){
//        break;
//      }
//    }
//    while  ( start_index >= 0 && start_index != pre_start_index);
//  }
  tests();

  return 0;
}


int check_test(char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]) {
  if ( is_same(result_string, expected_string ) ) { printf("%s\n",success_message); return 1; }
  else { fail_test(fail_message, input_string, result_string, expected_string); return 0; }
}

void fail_test(char fail_message[], char input_string[], char result_string[], char expected_string[]) {
  printf("!---- %s ----\n", fail_message);
  replaceNewLine(input_string,  '@'); 
  replaceNewLine(result_string,  '@'); 
  replaceNewLine(expected_string,  '@'); 
  printf("---[:0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF:]\n");
  printf("INP[:%s:]\n", input_string);
  printf("RES[:%s:]\n", result_string);
  printf("EXP[:%s:]\n", expected_string);
}

void cut_string(char cut[], char from[], int str, int end){
  for ( int i = str; i < end; i++) {
    cut[i - str] = from[i];
  }
}

int copy_to_string(char to[], char from[], int str_to, int end_to, int str_from, int end_from){
  if (str_to - end_to != str_from - end_from) return 0; // Failed copy
  int len = str_to - end_to;
  for (int i = 0; i < end_to; i++)
    to[i+str_to] = from[i + str_from];
  return 1; // Successful copy

}

/* get_line_length: returns length of line.
 * returns -1 if no newline.
 * returns -2 if somehow not terminated
 * String must at least be terminated by \0 
 * Includes \n in length */
int get_line_length(char line[]){
  int i;
  for (i = 0; line[i] != '\n' && line[i] != '\0'; i++);
  if (line[i] == '\n' && line[i+1] == '\0') return i;
  if (line[i] == '\0') return -1;
  return -2;
}

/* get_string_length: returns length of line.
 * returns -1 if no newline.
 * returns -2 if somehow not terminated
 * String must at least be terminated by \0 
 * Includes \n in length */
int get_string_length(char s[]){
  int i;
  for (i = 0; s[i] != '\0'; i++);
  return i;
}

void wrapLine(char line[],  char result[], int wrapwidth, int tabstop){
  int wrap_index = 0;
  int insert_index = 0;
  int start_index = 0;
  char wt_line[MAXLINE];
  int empty;
  while ((wrap_index = findWrapIndex(line, start_index, wrapwidth, tabstop)) - start_index > 0){
    wrap_index = findWrapIndex(line, start_index, wrapwidth, tabstop);
    int wrap_len = wrap_index - start_index;
    cut_string(wt_line, line, start_index, wrap_index + 1);
    int wt_start = 0;
    int wt_end = wrap_len + 2;
    int r_str = insert_index;
    int r_end = wrap_index + 2 + (insert_index - start_index);


    wt_line[wrap_len + 1] = '\n';
    if (!copy_to_string(result, wt_line, insert_index, wrap_index + 2 + (insert_index - start_index), 0, wrap_len + 2)) {
      printf("Failed to copy\n");
    }
    start_index = wrap_index + 1;
    insert_index = start_index + 1;
    result[insert_index+1] = '\0';
  }
}

int wrap_test(char test_message[], char success_message[], char fail_message[], char input_string[], char expected_string[], int wrapwidth, int tabstop){
  printf("%s: ",test_message);
  char result_string[MAXLINE];
  char input_string_copy[MAXLINE];
  char expected_string_copy[MAXLINE];
  copy(input_string_copy, input_string);
  copy(expected_string_copy, expected_string);
  wrapLine(input_string_copy, result_string, wrapwidth, tabstop); 
  return check_test(success_message, fail_message, input_string_copy, result_string, expected_string_copy);
}

int tests() {
  int passed_tests = 0;
  int total_tests = 0;


  passed_tests += wrap_test("ALLCHAR",          "PASS", "FAIL", "xxxxxxxxxxxxxxxx\n"    , "xxxxxxxxxxxxxxxx\n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("ALLBLANK",          "PASS", "FAIL", "                \n"    , "                \n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("ONEWRAP",          "PASS", "FAIL", "xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx\n"    , "xxxxxxxxxxxxxxxx\n xxxxxxxxxxxxxxxx\n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("MULTIBLANKWRAP",          "PASS", "FAIL", "xxx xxx xxx xx xxxxxxxxxxxxxxxxxx\n"    , "xxx xxx xxx xx xx\nxxxxxxxxxxxxxxxx\n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;

  return 0;
}


int is_same(char to[], char from[]) {
  int i;
  for ( i = 0; to[i] != '\0'; i++) if ( to[i] != from[i] ) return 0;
  return to[i] == from[i];
}


void replaceNewLine(char s[], char replacement) {
  for ( int i = 0; s[i] != '\0'; i++ ){
    if ( s[i] == '\n' ) { s[i] = replacement; }
  }
}




/* findWrapIndex: Cut lines larger than wrapwidth into multiple lines less than wrapwidth 
 * return -2 - No wraps, only \n
 * return -1 - No wraps, found \n in wrap
 * return i - Wraps at i */ 
int findWrapIndex(char line[], int start_index, int wrapwidth, int tabstop) {
  int check_index;
  int last_character_before_wrap = -1;
  for (check_index = start_index; line[check_index] != '\n' && check_index - start_index  <= wrapwidth; check_index++){
    char c = line[check_index];
    if ( c == ' ' ) {}
    else { last_character_before_wrap = check_index; }
  }
  if ( last_character_before_wrap == -1 ) { return  check_index - 1; }
  return last_character_before_wrap;
}





/* getLine: read a line into s, return length
 * return i -  Line length */
int getLine(char s[], int lim)
{
  int c, i;

  for (i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
    s[i] = c;
  if (c == '\n' || c == EOF)
    {
      s[i] = '\n';
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
