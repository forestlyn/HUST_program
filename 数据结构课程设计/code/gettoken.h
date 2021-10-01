#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum token_kind
{
  ERROR_TOKEN = 1,
  IDENT,     //标识符
  INT_CONST, //整形常量
  FLOAT_CONST,
  CHAR_CONST,
  STRING_CONST,
  LONG_CONST,
  KEYWORD,
  UNSIGNED,
  INT,
  FLOAT,
  CHAR,
  LONG,
  SHORT,
  DOUBLE,
  IF,
  ELSE,
  DO,
  WHILE,
  FOR,
  STRUCT,
  BREAK,
  SWITCH,
  CASE,
  TYPEDEF,
  RETURN,
  CONTINUE,
  VOID,
  CONST,
  STATIC,
  LB,         //左大括号
  RB,         //右大括号
  LM,         //左中括号
  RM,         //右中括号
  SEMI,       //分号31
  COMMA,      //逗号
  EQ,         //'=='
  NEQ,        //‘!=’
  ASSIGN,     //'='35
  LP,         //左括号
  RP,         //右括号
  TIMES,      //乘法
  DIVIDE,     //除法
  PLUS,       //加法40
  PLUSPLUS,   //自增运算
  MINUS,      //减法
  MINUSMINUS, //自减运算
  MOD,        //%
  POUND,      //井号42
  MORE,       //大于号
  LESS,       //小于号
  MOREEQUAL,  //大于等于
  LESSEQUAL,  //小于等于
  ANDAND,     //&&
  OROR,       //||
  ANNO,       //注释
  INCLUDE,    //头文件引用
  MACRO,      //宏定义
  ARRAY,      //数组
} token_kind;

const int KEYWORD_LEN = 15;
static char KeyWords[KEYWORD_LEN][20] = {
    "if", "else", "do", "while", "for", "struct", "break", "switch", "case", "typedef", "return",
    "continue", "void", "const", "static"};
const int KEYTYPE_LEN = 7;
static char KeyType[KEYTYPE_LEN][5] = {
    "U", "L", "LL", "UL", "LU", "LLU", "ULL"};
int isXnum(char c);
int isNum(char c);
int isRight(char *p);
int isRight_num(char c);
int addWord(char c, char *word);
int isLetter(char c);
int getToken(FILE *fp);
