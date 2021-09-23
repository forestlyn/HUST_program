#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum token_kind
{
  ERROR_TOKEN = 1,
  IDENT,     //��ʶ��
  INT_CONST, //���γ���
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
  LB,         //�������
  RB,         //�Ҵ�����
  LM,         //��������
  RM,         //��������
  SEMI,       //�ֺ�31
  COMMA,      //����
  EQ,         //'=='
  NEQ,        //��!=��
  ASSIGN,     //'='35
  LP,         //������
  RP,         //������
  TIMES,      //�˷�
  DIVIDE,     //����
  PLUS,       //�ӷ�40
  PLUSPLUS,   //��������
  MINUS,      //����
  MINUSMINUS, //�Լ�����
  MOD,        //%
  POUND,      //����42
  MORE,       //���ں�
  LESS,       //С�ں�
  MOREEQUAL,  //���ڵ���
  LESSEQUAL,  //С�ڵ���
  ANDAND,     //&&
  OROR,       //||
  ANNO,       //ע��
  INCLUDE,    //ͷ�ļ�����
  MACRO,      //�궨��
  ARRAY,      //����
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
