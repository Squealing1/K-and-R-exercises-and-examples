/* Reads a set of text lines and prints the longest one. */
#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8
#define WRAPWIDTH 16
#define TESTTABSTOP 8
#define TESTWRAPWIDTH 16

void emptyString(char s[]);
int checkStringTest(char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]);
int getLine(char s[], int lim);
void appendString(char to[], char from[]);
int getStringLen(char s[]);
int getSubString(char sub[], char s[], int str, int end);
void stripExtraNewlines(char s[]);
void appendChar(char to[], char from);
int getLastCharIndex(char s[]);
void replaceAllInString(char s[], char to, char from);
void replaceNewLine(char s[], char replacement); 
int isSame(char to[], char from[], int limit);
void failTest(char fail_message[], char input_string[], char result_string[], char expected_string[]);
int stringTest(char test_message[], char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]);
int tests();
void copy(char to[], char from[]);

int main(void)
{
  char line[MAXLINE];
  int len;
  // while((len = getLine(line, MAXLINE)) > 1) {
  //   printf("%s",append);
  // }

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

/* Find index of first character of substring in from string */
int findString(char from[], char substring[], int start_search_index){
  int sub_len = getStringLen(substring);
  int from_len = getStringLen(from);
  printf("%d\n", -110);
  if (sub_len > from_len) return -1;
  else if (sub_len == from_len){
    if (isSame(from, substring, MAXLINE)) return 0;
    else return -1;
  }
  printf("%d\n", -110);
  int start_index = start_search_index; 
  int end_index = start_search_index;
  int in_substring = 0;
  for (int i = start_search_index; i < from_len; i++){
    if (!in_substring) {
      start_index = i;
    }
    end_index = i;
    if ( from[i] == substring[end_index-start_index] ) {
      if (end_index - start_index == sub_len - 1) {
        return start_index; // Found sub string
      }
      in_substring = 1;
    }
    else {
      in_substring = 0;
      start_index = i;
    }
  }
  return -1; // Negative indicates substring was not found
}

int checkIntTest(char test_message[], char success_message[], char fail_message[], int result_int, int expected_int){
  printf("---------- %s ----------\n", test_message);
  if ( result_int == expected_int ) {
    printf("%s\n", success_message);
    return 1;
  }
  else{
    printf("%s: res: %d, exp: %d\n", fail_message, result_int, expected_int);
    return 0;
  }
}

  

int checkStringTest(char success_message[], char fail_message[], char input_string[], char result_string[], char expected_string[]) {
  printf("---[:0123456789ABCDEFG0123456789ABCDEFG0123456789ABCDEFG0123456789ABCDEFG:]\n");
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

  passed_tests += checkIntTest("FIND_SUBSTRING", "PASS", "FAIL", findString("xxxSUBSTRINGxxx", "SUBSTRING", 0), 3); total_tests++;
  passed_tests += checkIntTest("DONT_FIND_SUBSTRING", "PASS", "FAIL", findString("xxxSUBSTRINGxxx", "PIG", 0), -1); total_tests++;
  passed_tests += checkIntTest("DONT_FIND_SUBSTRING_BIG_SUBSTRING", "PASS", "FAIL", findString("xxx", "xxxxxxxx", 0), -1); total_tests++;
  passed_tests += checkIntTest("SAMESIZEFIND", "PASS", "FAIL", findString("DOG", "DOG", 0), 0); total_tests++;
  passed_tests += checkIntTest("LATERSEARCH", "PASS", "FAIL", findString("DOGBONEDOG", "DOG", 3), 7); total_tests++;

  printf("Pass %d/%d tests.\n",passed_tests,total_tests);

  return 0;
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
  return checkStringTest(success_message, fail_message, input_string, result_string, expected_string); 
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
