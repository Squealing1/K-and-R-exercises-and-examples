/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define WRAPWIDTH 16
#define TESTTABSTOP 8
#define TESTWRAPWIDTH 16

int getLine(char line[], int maxline);
int wrapLineOnce(char line[], char w_line[], int start_index, int wrapwidth, int tabstop);
void wrapLine(char line[],  char result_line[], int wrapwidth, int tabstop);
void copy(char to[], char from[]);
void append_string(char to[], char from[], int empty);
void replaceNewLine(char s[], char replacement); 
int is_same(char to[], char from[]);
void fail_test(char fail_message[], char input_string[], char result_string[], char expected_string[]);
int tests();

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
  printf("---[:0123456789ABCDEF0123456789ABCDEF:]\n");
  printf("INP[:%s:]\n", input_string);
  printf("RES[:%s:]\n", result_string);
  printf("EXP[:%s:]\n", expected_string);
}
void append_string(char to[], char from[], int empty) {
  int len;
  if ( empty ) len = 0;
  else for (len = 0; to[len] != '\0'; len++);
  int i;
  for (i = 0; from[i] != '\0'; i++) to[i+len] = from[i];
  to[i+len] = '\0';
}

int lineLength(char line[]) {
  int i;
  for (i = 0; line[i] != '\n' && line[i] != '\0'; i++);
  return i;
}

void wrapLine(char line[],  char result_line[], int wrapwidth, int tabstop){
  int start_index = 0;
  int linelength = lineLength(line);
  char dt_line[MAXLINE];
  int pre_start_index = 0;
  int empty;
  do {
    pre_start_index = start_index;
    start_index = wrapLineOnce(line, dt_line, start_index, wrapwidth, tabstop);
    if (pre_start_index == 0) empty = 1; 
    else empty = 0; 
    append_string(result_line, dt_line, empty);
  } while( start_index < linelength );

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
  passed_tests += wrap_test("BLANKTHENCHAR",    "PASS", "FAIL", "  xxxxxxxxxxxxxx\n"    , "  xxxxxxxxxxxxxx\n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("BLANKTHENCHAR",    "PASS", "FAIL", "   xxxxxxxxxxxxxx\n"   , "   xxxxxxxxxxxxxx\n", TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("ALLCHARPASTWRAP",  "PASS", "FAIL", "xxxxxxxxxxxxxxxxx   xxxx\n"   , "xxxxxxxxxxxxxxxxx  xxxx\n" , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("CHARSTHENBLNK" ,   "PASS", "FAIL", "xxxxxxxxxxxxxxxxx\n"   , "xxxxxxxxxxxxxxxxx\n" , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("NOWRAPSPACE",      "PASS", "FAIL", "xxxxxxxxx xxxxxx\n"    , "xxxxxxxxx xxxxxx\n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("ALLSPACE",         "PASS", "FAIL", "                \n"    , "                \n"  , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("WRAPONCE",         "PASS", "FAIL", "xxxxxxxx    xxxxxxx\n" , "xxxxxxxx\nxxxxxxx\n" , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("WRAPThrice",       "PASS", "FAIL", "xxxxxxxx    xxxxxxx    xxxxxxx    xxxxxxx\n" , "xxxxxxxx\nxxxxxxx\nxxxxxxx\nxxxxxxx\n" , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("WRAPThrice",       "PASS", "FAIL", "xxxxxxxx    xxxxxxx    xxxxxxx    xxxxxxx\n" , "xxxxxxxx\nxxxxxxx\nxxxxxxx\nxxxxxxx\n" , TESTWRAPWIDTH, TESTTABSTOP); total_tests++;

  printf("Passed %d/%d tests\n", passed_tests, total_tests);

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
int wrapLineOnce(char line[], char w_line[], int start_index, int wrapwidth, int tabstop) {
  int column = 0;
  int prev_ws_i = -1; // The first whitespace character before the last end of a word
  int prev_char_i = -1; // The start of the word after the wrap
  int i;
  int past_wrapwidth = 0;


  for(i = start_index; line[ i] != '\n' && line[ i] != '\0'; i++) {
    if ( line[ i] == ' ' ) { // Space found
       if ( prev_char_i >= prev_ws_i ) {
         prev_ws_i = i;
       }
       column++;
    }
    else { // Character found
       if (column > wrapwidth && prev_ws_i != -1) { past_wrapwidth = 1; break; } // Went past wrapwidth
       if ( prev_char_i <= prev_ws_i ) {
         prev_char_i = i;
       }
       column++;
      }
  }

  int new_start_index;

  if ( prev_ws_i == -1 || (!past_wrapwidth)) {
    cutLine(line, w_line, start_index, i); 
    new_start_index = i;
  }
  else {
    cutLine(line, w_line, start_index, prev_ws_i);
    new_start_index =  prev_char_i;
  }

  return new_start_index;


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
