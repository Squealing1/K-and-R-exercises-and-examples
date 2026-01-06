/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 256
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
void append_string(char to[], char from[], int empty);

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
  int result;
  if ( is_same(result_string, expected_string ) ) { printf("%s\n",success_message); 
    result = 1; }
  else { fail_test(fail_message, input_string, result_string, expected_string); 
    result = 0; }
  printf("E----------------------------------E\n");
  return result;
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
  for ( int i = str; i <= end; i++) {
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
  int white_count = 0;
  int char_count = 0;
  int wrap_count = 0;
  for ( int i; line[i] != '\n'; i++){
    if ( line[i] == ' ' ) {


  }
}


int string_test(char test_message[], char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]){
    printf("----------- %s ----------\n", test_message);
    char result_string_copy[MAXLINE];
    char input_string_copy[MAXLINE];
    char expected_string_copy[MAXLINE];
    copy(input_string_copy, input_string);
    copy(expected_string_copy, expected_string);
    copy(result_string_copy, result_string); 
    return check_test(success_message, fail_message, input_string_copy, result_string_copy, expected_string_copy);
  }

void wrap_test(char input_string[], char result_string[],  int wrapwidth, int tabstop){
  char input_string_copy[MAXLINE];
  char expected_string_copy[MAXLINE];
  copy(input_string_copy, input_string);
  wrapLine(input_string_copy, result_string, wrapwidth, tabstop); 
}

void append_string(char to[], char from[], int empty){
  int len_to;
  if (empty) {len_to = 0; copy(to,"\0"); }
  else for(len_to = 0; to[len_to] != '\0'; len_to++);
  int len_from;
  for (len_from = 0; from[len_from] != '\0'; len_from++) to[len_to + len_from] = from[len_from];
  to[len_to + len_from] = '\0';
}

int tests() {
  int passed_tests = 0;
  int total_tests = 0;
  char result_string[MAXLINE];
  char input_string[MAXLINE];
  char expected_string[MAXLINE];

  copy(input_string,    "THEDOG\n");
  copy(expected_string, "THEDOG\n");
  copy(result_string, input_string);
  passed_tests += string_test("COPYTHEMALL", "PASS","FAIL", input_string, result_string, result_string);

  copy(input_string,    "N/A\n");
  copy(expected_string, "THE DOG RAN\n");
  copy(result_string, "THE DOG");
  append_string(result_string, " RAN\n", 0);
  passed_tests += string_test("APENDSTRING", "PASS","FAIL", input_string, result_string, expected_string);

  copy(expected_string, "THE DOG RAN FAST\n");
  append_string(result_string, "THE DOG RAN FAST\n", 1);
  passed_tests += string_test("APENDTOEMPTYSTRING", "PASS","FAIL", input_string, result_string, expected_string);

  copy(expected_string, "THE DOG RAN\n");
  append_string(result_string, "THE", 1);
  append_string(result_string, " DOG", 0);
  append_string(result_string, " RAN\n", 0);
  passed_tests += string_test("APENDSTRINGTHRICE", "PASS","FAIL", input_string, result_string, expected_string);

  copy(expected_string, "THE DOG RAN FAST\n");
  copy(result_string, "");
  append_string(result_string, "THE DOG RAN FAST\n", 1);
  passed_tests += string_test("APENDTOEMPTYSTRING", "PASS","FAIL", input_string, result_string, expected_string);

  copy(input_string,    "xxxxxxxxxxxxxxxx\n");
  copy(expected_string, "xxxxxxxxxxxxxxxx\n");
  copy(result_string, "");
  wrap_test(input_string,    result_string, WRAPWIDTH, TABSTOP   ); total_tests++;
  passed_tests += string_test("ALLCHAR", "PASS","FAIL", input_string, result_string, expected_string); total_tests++;

  copy(input_string,    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
  copy(expected_string, "xxxxxxxxxxxxxxxx\nxxxxxxxxxxxxxxxx\n");
  copy(result_string, "");
  wrap_test(input_string,    result_string, WRAPWIDTH, TABSTOP   ); total_tests++;
  passed_tests += string_test("BIGCHAR", "PASS","FAIL", input_string, result_string, expected_string); total_tests++;

  copy(input_string,    "xxxxxxxxxxxxxxx     xxxxxxxxxxxx\n");
  copy(expected_string, "xxxxxxxxxxxxxxx\n     xxxxxxxxxxxxxxxx\n");
  copy(result_string, "");
  wrap_test(input_string,    result_string, WRAPWIDTH, TABSTOP   ); total_tests++;
  passed_tests += string_test("BIGCHAR", "PASS","FAIL", input_string, result_string, expected_string); total_tests++;

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
  int last_white_before_wrap = -1;
  for (check_index = start_index; line[check_index] != '\n' && check_index - start_index  <= wrapwidth; check_index++){
    char c = line[check_index];
    if ( c == ' ' ) { last_white_before_wrap = check_index; }
    else { last_character_before_wrap = check_index; }
  }
  
  if (check_index - start_index > wrapwidth) { 
    if ( last_character_before_wrap == -1 ) { return  check_index - 1; }
    return last_character_before_wrap;
  }
  else {
    if ( last_character_before_wrap != -1 && last_white_before_wrap != -1 ) {
      if ( last_character_before_wrap > last_white_before_wrap ) return last_character_before_wrap;
      else return last_white_before_wrap;
    }
    else {
      return check_index;
    }
  }
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
  while (from[i] != '\0'){
    to[i] = from[i];
    ++i;
  }
  to[i] = '\0';
}
