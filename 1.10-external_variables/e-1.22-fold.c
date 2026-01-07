/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define WRAPWIDTH 16
#define TESTTABSTOP 8
#define TESTWRAPWIDTH 16

int wrap_test(char test_message[], char success_message[], char fail_message[], char input_string[], char expected_string[], int wrapwidth, int tabstop);
void emptyString(char s[]);
int checkTest(char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]);
int getLine(char s[], int lim);
void appendString(char to[], char from[]);
int getStringLen(char s[]);
int getSubString(char sub[], char s[], int str, int end);
void stripExtraNewlines(char s[]);
void wrapLine(char line[], char append[], int wrapwidth, int tabstop);
void appendChar(char to[], char from);
int getLastCharIndex(char s[]);
void replaceAllInString(char s[], char to, char from);
void replaceNewLine(char s[], char replacement); 
int isSame(char to[], char from[], int limit);
void failTest(char fail_message[], char input_string[], char result_string[], char expected_string[]);
int stringTest(char test_message[], char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]);
int tests();
void copy(char to[], char from[]);
int wrapOnce(char line[], char result_line[], char wt_line[], int wrap_count);

int main(void)
{
  char append[MAXLINE] = "";
  char append_simple[MAXLINE] = "";
  char line[MAXLINE];
  int len;
  int wrap = 0;
  while((len = getLine(line, MAXLINE)) > 0) {
    wrapLine(line, append, WRAPWIDTH, TABSTOP);
    printf("%s",append);
  }

  tests();

  return 0;
}
int isSame(char to[], char from[], int limit) {
  int i;
  for ( i = 0; to[i] != '\0' && from[i] != '\0' && i < limit; i++) if ( to[i] != from[i] ) return 0;
  return to[i] == from[i];
}
/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
int checkTest(char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]) {
  printf("---[:0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF:]\n");
  char is_c[MAXLINE];
  char rs_c[MAXLINE];
  char es_c[MAXLINE];
  copy(is_c, input_string); 
  copy(rs_c, result_string); 
  copy(es_c, expected_string); 
  int is_same = isSame(result_string, expected_string , MAXLINE);
  replaceNewLine(is_c,  '@'); 
  replaceNewLine(rs_c,  '@'); 
  replaceNewLine(es_c,  '@'); 
  printf("INP[:%s:]\n", is_c);
  printf("RES[:%s:]\n", rs_c);
  printf("EXP[:%s:]\n", es_c);
  int has_passed;
  if ( is_same ) { 
    printf("%s\n",success_message); has_passed = 1; 
  }
  else { 
    failTest(fail_message, input_string, result_string, expected_string); has_passed = 0; 
  }
  return has_passed;
}
void replaceNewLine(char s[], char replacement) {
  replaceAllInString(s, replacement, '\n');
}


void failTest(char fail_message[], char input_string[], char result_string[], char expected_string[]) {
  printf("!-%s-!\n", fail_message);
//  printf("---[:0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF:]\n");
//  printf("INP[:%s:]\n", input_string);
//  printf("RES[:%s:]\n", result_string);
//  printf("EXP[:%s:]\n", expected_string);

}

int wrap_test(char test_message[], char success_message[], char fail_message[], char input_string[], char expected_string[], int wrapwidth, int tabstop){
  printf("---------- %s ----------\n", test_message);
  char result_string[MAXLINE];
  char input_string_copy[MAXLINE];
  char expected_string_copy[MAXLINE];
  copy(input_string_copy, input_string);
  copy(expected_string_copy, expected_string);
  wrapLine(input_string_copy, result_string, wrapwidth, tabstop); 
  return checkTest( success_message, fail_message, input_string_copy, result_string, expected_string_copy);
}
int tests() {
  int passed_tests = 0;
  int total_tests = 0;


  passed_tests += stringTest("TESTTEST", "PASS", "FAIL", "DOG", "DOG", "DOG"); total_tests++;
  passed_tests += !stringTest("FAILTEST", "FAIL", "PASS", "DOG", "CAT", "DOG"); total_tests++;

  char result_string[MAXLINE];
  getSubString(result_string, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 35);
  
  passed_tests += stringTest("SUBSTRINGFULL35", "PASS", "FAIL", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", result_string, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"); total_tests++;


  getSubString(result_string, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 10);

  passed_tests += stringTest("SUBSTRINGPARTIAL_0_TO_10_OF_35", "PASS", "FAIL", "0123456789A", result_string, "0123456789A"); total_tests++;

  emptyString(  result_string);
  appendChar(result_string, '\n');
  passed_tests += stringTest("APPENDCHARNEWLINE", "PASS", "FAIL", "\n", result_string, "\n"); total_tests++;

  emptyString(  result_string);
  appendChar(result_string, '\n');
  appendChar(result_string, '\n');
  passed_tests += stringTest("APPENDCHARNEWLINETWICE", "PASS", "FAIL", "\n\n", result_string, "\n\n"); total_tests++;

  emptyString(  result_string);
  appendString(result_string, "\n");
  appendString(result_string, "\n");
  passed_tests += stringTest("APPENDSTRINGNEWLINETWICE", "PASS", "FAIL", "\n\n", result_string, "\n\n"); total_tests++;

  char input_parts[MAXLINE] = "";
  emptyString(  result_string);
  appendChar(input_parts, 'x');
  appendChar(input_parts, '\n');
  appendString(result_string, input_parts);
  passed_tests += stringTest("APPENDBUILT_FROM_CHAR_STRING_X_NL", "PASS", "FAIL", "x\n", result_string, "x\n"); total_tests++;

  emptyString(  input_parts);
  emptyString(  result_string);
  appendChar(input_parts, '\n');
  appendString(result_string, input_parts);
  printf("result_string: %s\n",result_string);
  passed_tests += stringTest("APPENDBUILT_FROM_CHAR_STRING_NL", "PASS", "FAIL", "\n", result_string, "\n"); total_tests++;


  passed_tests += wrap_test("ALLCHAR","PASS", "FAIL", "xxxxxxxxxxxxxxxx\n", "xxxxxxxxxxxxxxxx\n", TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("NEWLINE","PASS", "FAIL", "\n", "\n", TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("ONEBLANK","PASS", "FAIL", " \n", " \n", TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("ONEWRAP","PASS", "FAIL", "xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx\n", "xxxxxxxxxxxxxxxx\n xxxxxxxxxxxxxxx\nx\n", TESTWRAPWIDTH, TESTTABSTOP); total_tests++;
  passed_tests += wrap_test("MULTIBLANKWRAP","PASS", "FAIL", "xxx xxx xxx xx xxxxxxxxxxxxxxxxxx\n", "xxx xxx xxx xx x\nxxxxxxxxxxxxxxxx\nx\n", TESTWRAPWIDTH, TESTTABSTOP); total_tests++;

  printf("Pass %d/%d tests.\n",passed_tests,total_tests);

  return 0;
}
void wrapLine(char line[],  char result_line[], int wrapwidth, int tabstop){
    int len;
    emptyString(    result_line);
    len = getStringLen(line);
    char wt_line[MAXLINE] = "";
    int i;
    int wrap_count = 0;
    for (int i = 0; i <= len; i+=1) { 
      appendChar(wt_line,line[i]);
      if ( wrap_count > wrapwidth - 2) {
        int left_over_blanks = wrapOnce(line, result_line, wt_line, wrap_count);
        wrap_count = left_over_blanks;
      }
      else
      {
        wrap_count++;
      }
    }
    int len_wt = getStringLen(wt_line);
    if (len_wt > 0){
      appendString(result_line, wt_line);
      stripExtraNewlines(result_line);
    }
}

int wrapOnce(char line[], char result_line[], char wt_line[], int wrap_count){
        char wt_before[MAXLINE] = "";
        char wt_after[MAXLINE] = "";
        int last_char = getLastCharIndex(wt_line);
        if (last_char != -1){
          int wt_len = getStringLen(wt_line);
          getSubString(wt_before, wt_line, 0, last_char);
          getSubString(wt_after, wt_line, last_char + 1, wt_len);
          appendString(result_line,wt_before);
          appendString(result_line, "\n");
        }
        else {
          appendString(result_line, "\n");
        }

        appendString(result_line, wt_after);
        int wt_after_len = getStringLen(wt_after);
        emptyString(        wt_line);
        emptyString(        wt_before);
        emptyString(        wt_after);
        return wt_after_len;
    }


void replaceAllInString(char s[], char to, char from){
  int len = getStringLen(s);
  for(int i = 0; i < len; i++) {
    if (s[i] == from){
      s[i] = to;
    }
  }
}

int getLastCharIndex(char s[]){
  int len = getStringLen(s);
  int last_char = -1;
  for (int i = 0; i < len; i++){
    if (s[i] != ' ' && s[i] != '\n' && s[i] != '\0') last_char = i;
  }
  return last_char;
}

void stripExtraNewlines(char s[]){
    // Strip extra newlines
    int a_len = getStringLen(s);
    int i;
    for(i = a_len; s[i] == '\n' || s[i] == '\0'; i--);
    if (s[i] == '\0') printf("STRIPING WENT WRONG!\n");
    s[i+1] = '\n';
    s[i+2] = '\0';
}

int getSubString(char sub[], char s[], int str, int end){
  int len = end - str;
  int i;
  for( i = 0; i <= len; i++) {
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

void emptyString(char s[]){
  s[0] = '\0';
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

int stringTest(char test_message[], char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]){
  printf("---------- %s ----------\n", test_message);
  return checkTest(success_message, fail_message, input_string, result_string, expected_string); 
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
