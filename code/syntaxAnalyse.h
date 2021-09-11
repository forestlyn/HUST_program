#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ASTTree
{
  struct ASTTree *l;
  struct ASTTree *r;
  int type;
  struct data
  {
    int type;
    char data[20];
  } data;
} ASTTree;

typedef struct VariableDefNode
{
  int size; // define num
  int type[20];
  char variable[20][50]; // names
  struct VariableDefNode *next;
} VDN;

typedef struct Fun
{
  int type;
  ASTTree *Vardef; //����
  char name[50];
  struct Fun *next;
} Fun;

enum DataType
{
  EXTDEFLIST = 1,
  EXTVARDEF,
  EXTVARTYPE,
  EXTVARLIST,         //�ⲿ���������н��
  EXTVAR,             //�ⲿ���������
  FUNCDEF,            //����������
  FUNCRETURNTYPE,     //��������ֵ���ͽ��
  FUNCNAME,           //���������
  FUNCFORMALPARALIST, //������ʽ�������н��
  FUNCFORMALPARADEF,  //������ʽ�������10
  FUNCFORMALPARATYPE, //�����β����ͽ��
  FUNCFORMALPARA,     //�����β������
  FUNCBODY,           //��������
  LOCALVARDEFLIST,    //�ֲ������������н��
  LOCALVARDEF,        //�ֲ�����������15
  LOCALVARTYPE,       //�ֲ��������ͽ��
  LOCALVARNAMELIST,   //�ֲ�����������
  LOCALVARNAME,       //�ֲ�������
  STATELIST,          //������н��
  OPERAND,            //���������20
  OPERATOR,           //��������
  EXPRESSION,         //���ʽ
  IFPART,             // if��䲿��
  ELSEPART,           // else����
  IFSTATEMENT,        // if���25
  IFELSESTATEMENT,    // if-else���
  WHILESTATEMENT,     // while�����
  WHILEPART,          // while���������
  WHILEBODY,          // while�����
  FORSTATEMENT,       // for�����30
  FORPART,            // for�������
  FORPART1,           // for�������һ
  FORPART2,           // for���������
  FORPART3,           // for���������
  FORBODY,            // for�����35
  RETURNSTATEMENT,    // return���
  BREAKSTATEMENT,     // break���
  DOWHILESTATEMENT,   // do-whileѭ�����
  DOWHILEBODY,        // do-while�����
  DOWHILECONDITION,   // do-while����40
  CONTINUESTATEMENT,  // continue���
  FUNCCLAIM,          //��������
  ARRAYDEF,           //���鶨��
  ARRAYTYPE,          //��������
  ARRAYNAME,          //������45
  ARRAYSIZE,          //�����С
  INCLUDELIST,        //ͷ�ļ�����
  INCLUDENAME,        //ͷ�ļ�����
  FUNUSE,             //��������
  MACROLIST,          //�궨������
  MACRONAME,          //�궨������
};

void syntaxAnalyse(); //��ʼ

ASTTree *init_AST(); //��ʼ������

ASTTree *program(); //��ʼ����

ASTTree *ExtDefList(); //�ⲿ��������

ASTTree *ExtDef(); //�ж��ⲿ����

ASTTree *ArrayDef();

ASTTree *ExtVarDef(); //�ⲿ���б���

ASTTree *FuncDef(); //��������

ASTTree *FormParaList(int flag); //�����β�����

ASTTree *FormParaDef(); //�����βδ���

ASTTree *CompState(); //������������

ASTTree *LocalVarDefList(); //�����ֲ�����

ASTTree *StateList(); //�����������

ASTTree *Statement(); //�������

ASTTree *Expression(int endsym);

ASTTree *headFile();

ASTTree *macroFile();

char Precede(int c1, int c2);

void returnToken(FILE *fp);

void showType(int type);

void PreorderTranverse(ASTTree *root, int depth);

int can(char *name, int flag_, int type);

int checkName(char *name, int type);

int checkType(int a, int b);

Fun *checkFun(char *name);

ASTTree *FunUse(Fun *f);
