#include "syntaxAnalyse.h"
#include "gettoken.h"

using namespace std;

extern char token_text[20];
extern char string_num[20];
extern int lines;
extern FILE *fp;

int w, type; // token type
int error = 0;
VDN *Vroot; // 变量链表根节点
int isVoid, hasReturn, isInRecycle = 0;

void syntaxAnalyse()
//输出
{
  ASTTree *root = program();
  if (root == NULL || error == 1)
  {
    printf("syntax error!\n");
    return;
  }
  else
#error wait to finish
    ;
}

ASTTree *program()
//开始分析
{
  w = getToken(fp);
  while (w == ANNO || w == INCLUDE)
  {
    w = getToken(fp);
  }
  Vroot = (VDN *)malloc(sizeof(VDN));
  Vroot->size = 0;
  Vroot->next = NULL;
  ASTTree *p = ExtDefList();
  if (p != NULL)
  {
    if (!isVoid && !hasReturn)
    {
      printf("Error: no void miss return value\n");
      exit(0);
    }
    ASTTree *root = p;
    root->type = EXTDEFLIST;
    return root;
  }
  else
  {
    error = 1;
    return NULL;
  }
}
ASTTree *ExtDefList()
//处理外部定义，左结点存具体定义，右节点是后续外部定义结点
{
  if (error || w == -1)
    return NULL;
  ASTTree *root = init_AST();
  root->type = EXTDEFLIST;
  root->l = ExtDef();
  w = getToken(fp);
  while (w == ANNO || w == INCLUDE)
    w = getToken(fp);
  root->r = ExtDefList();
  return root;
}

ASTTree *ExtDef()
//判断外部定义，判断是变量还是函数，进而调用其它函数处理
{
  int a;
  if (error)
    return NULL;
  if (w != INT && w != FLOAT && w != CHAR && w != LONG && w != SHORT && w != DOUBLE && w != VOID)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong external define\n");
    exit(0);
  }
  type = w;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w != IDENT && w != ARRAY)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong external define\n");
    exit(0);
  }
  a = w;
  char text[20];
  strcpy(text, token_text);
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  strcpy(token_text, text);
  ASTTree *p;
  if (w == LP)
    p = FuncDef();
  else if (a == ARRAY)
    p = ArrayDef();
  else
    p = ExtVarDef();
  return p;
}

ASTTree *ArrayDef()
{
  if (type == VOID)
  {
    printf("Error in line %d\n", lines);
    printf("Error: can't type void array\n");
    exit(0);
  }
  ASTTree *root, *p;
  root = init_AST();
  p = init_AST();
  root->type = ARRAYDEF;
  p->type = ARRAYTYPE;
  if (type == INT)
    strcpy(p->data.data, "int");
  if (type == FLOAT)
    strcpy(p->data.data, "float");
  if (type == CHAR)
    strcpy(p->data.data, "char");
  if (type == LONG)
    strcpy(p->data.data, "long");
  if (type == SHORT)
    strcpy(p->data.data, "short");
  if (type == DOUBLE)
    strcpy(p->data.data, "double");

  root->l = p;
  p = init_AST();
  p->type = ARRAYNAME;
  strcpy(p->data.data, token_text);
  root->r = p;
  ASTTree *q = init_AST();
  q->type = ARRAYSIZE;
  strcpy(q->data.data, string_num);
  p->l = q;
  return root;
}

ASTTree *ExtVarDef()
//外部序列变量
{
  if (error)
    return NULL;
  if (type == VOID)
  {
    printf("Error in line %d\n", lines);
    printf("Error: can't type void variables\n");
    exit(0);
  }
  if (!can(token_text))
  {
    printf("Error in line %d\n", lines);
    printf("Error: can't define %s twice\n", token_text);
    exit(0);
  }
  ASTTree *root, *p;
  root = init_AST();
  p = init_AST();
  root->type = EXTVARDEF;
  p->type = EXTVARTYPE;
  p->data.type = type;
  if (type == INT)
    strcpy(p->data.data, "int");
  if (type == FLOAT)
    strcpy(p->data.data, "float");
  if (type == CHAR)
    strcpy(p->data.data, "char");
  if (type == LONG)
    strcpy(p->data.data, "long");
  if (type == SHORT)
    strcpy(p->data.data, "short");
  if (type == DOUBLE)
    strcpy(p->data.data, "double");

  root->l = p;
  p = init_AST();
  p->type = EXTVARLIST;
  root->r = p;

  ASTTree *q = init_AST();
  q->type = EXTVAR;
  strcpy(q->data.data, token_text);
  p->l = q;

  while (1)
  {
    if (w != COMMA && w != SEMI)
    {
      printf("Error in line %d\n", lines);
      printf("Error: wrong external define\n", token_text);
      exit(0);
    }
    if (w == SEMI)
      return root;
    w = getToken(fp);
    if (w != IDENT)
    {
      printf("Error in line %d\n", lines);
      printf("Error: wrong external define\n", token_text);
      exit(0);
    }

    if (!can(token_text))
    {
      printf("Error in line %d\n", lines);
      printf("Error: can't define %s twice\n", token_text);
      exit(0);
    }

    q = init_AST();
    q->type = EXTVARLIST;
    p->r = q;
    p = q;

    q = init_AST();
    q->type = EXTVAR;
    strcpy(q->data.data, token_text);
    p->l = q;
    w = getToken(fp);

    while (w == ANNO)
      w = getToken(fp);
  }
}

ASTTree *FuncDef()
{
  if (error)
    return NULL;
  ASTTree *root, *p;
  root = init_AST();
  p = init_AST();
  root->type = FUNCDEF;
  p->type = FUNCRETURNTYPE;
  p->data.type = type;
  if (type == INT)
    strcpy(p->data.data, "int");
  if (type == FLOAT)
    strcpy(p->data.data, "float");
  if (type == CHAR)
    strcpy(p->data.data, "char");
  if (type == LONG)
    strcpy(p->data.data, "long");
  if (type == SHORT)
    strcpy(p->data.data, "short");
  if (type == DOUBLE)
    strcpy(p->data.data, "double");
  if (type == VOID)
  {
    strcpy(p->data.data, "void");
    isVoid = 1;
  }
  root->l = p;

  ASTTree *q = init_AST();
  q->type = FUNCNAME;
  strcpy(q->data.data, token_text);
  root->r = q;

  VDN *lastVDN = Vroot;
  while (lastVDN->next)
    lastVDN = lastVDN->next;
  lastVDN->next = (VDN *)malloc(sizeof(VDN));
  lastVDN = lastVDN->next;
  lastVDN->next = NULL;
  lastVDN->size = 0;

  q->l = FormParaList(0);

  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);

  if (w == SEMI)
  {
    q->r = NULL;
    root->type = FUNCCLAIM;
  }
  else if (w == LB)
  {
    q->r = CompState();
#error
  }
  else
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong function def\n", token_text);
    exit(0);
  }
  return root;
}

ASTTree *FormParaList(int flag)
//函数形参，flag记录是否是第一个参数结点
{
  if (error)
    return NULL;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w == RP)
    return NULL;

  if (!flag && w == COMMA)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong function def\n", token_text);
    exit(0);
  }
  else if (w == COMMA && flag)
  {
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
  }
  ASTTree *root = init_AST();
  root->type = FUNCFORMALPARALIST;
  root->l = FormParaDef();
  root->r = FormParaList(1);
  return root;
}
ASTTree *FormParaDef()
//函数形参定义
{
  if (error)
    return NULL;
  if (w != INT && w != FLOAT && w != CHAR && w != LONG && w != SHORT && w != DOUBLE)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong  formparadef\n", token_text);
    exit(0);
  }
  type = w;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w != IDENT)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong  formparadef\n", token_text);
    exit(0);
  }
  ASTTree *root, *p;
  root = init_AST();
  p = init_AST();
  root->type = FUNCFORMALPARADEF;
  p->type = FUNCFORMALPARATYPE;
  p->data.type = type;
  if (type == INT)
    strcpy(p->data.data, "int");
  if (type == FLOAT)
    strcpy(p->data.data, "float");
  if (type == CHAR)
    strcpy(p->data.data, "char");
  if (type == LONG)
    strcpy(p->data.data, "long");
  if (type == SHORT)
    strcpy(p->data.data, "short");
  if (type == DOUBLE)
    strcpy(p->data.data, "double");
  root->l = p;

  p = init_AST();
  p->type = FUNCFORMALPARA;

  if (!can(token_text))
  {
    printf("Error in line %d\n", lines);
    printf("Error: can't define %s twice\n", token_text);
    exit(0);
  }
  strcpy(p->data.data, token_text);
  root->r = p;
  return root;
}

ASTTree *CompState()
//分析函数主体
{
  if (error)
    return NULL;

  ASTTree *root = init_AST();
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);

  if (w == INT || w == DOUBLE || w == CHAR || w == LONG || w == SHORT || w == FLOAT)
    root->l = LocalVarDefList();
  root->r = StateList();
  if (w == RB)
    return root;
  else
  {
    printf("Error in line %d\n", lines);
    printf("Error: error in compstate\n");
    exit(0);
  }
}

ASTTree *LocalVarDefList()
//内部节点变量
{
  if (error)
    return NULL;
  ASTTree *root, *p;
  root = init_AST();
  p = init_AST();
  root->type = LOCALVARDEFLIST;
  p->type = LOCALVARDEF;
  root->l = p;

  ASTTree *q = init_AST();
  q->type = LOCALVARTYPE;
  q->data.type = w;
  if (w == INT)
    strcpy(p->data.data, "int");
  if (w == FLOAT)
    strcpy(p->data.data, "float");
  if (w == CHAR)
    strcpy(p->data.data, "char");
  if (w == LONG)
    strcpy(p->data.data, "long");
  if (w == SHORT)
    strcpy(p->data.data, "short");
  if (w == DOUBLE)
    strcpy(p->data.data, "double");
  p->l = q;
  p = q;

  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  q = init_AST();
  q->type = LOCALVARNAMELIST;
  p->r = q;

  if (w != IDENT)
  {
    printf("Error in line %d\n", lines);
    printf("Error: error in local vardef\n");
    exit(0);
  }
  p = q;
  if (!can(token_text))
  {
    printf("Error in line %d\n", lines);
    printf("Error: can't define %s twice\n", token_text);
    exit(0);
  }
  q = init_AST();
  q->type = LOCALVARNAME;
  strcpy(q->data.data, token_text);
  p->l = q;

  while (1)
  {
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w == SEMI)
    {
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
      break;
    }
    else if (w == COMMA)
    {
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);

      if (w != IDENT)
      {
        printf("Error in line %d\n", lines);
        printf("Error: error in local vardef\n");
        exit(0);
      }
      else if (!can(token_text))
      {
        printf("Error in line %d\n", lines);
        printf("Error: can't define %s twice\n", token_text);
        exit(0);
      }

      q = init_AST();
      q->type = LOCALVARNAMELIST;
      p->r = q;
      p = q;

      q = init_AST();
      q->type = LOCALVARNAME;
      strcpy(q->data.data, token_text);
      p->l = q;
    }
    else
    {
      printf("Error in line %d\n", lines);
      printf("Error: wrong def of local variables\n");
      exit(0);
    }
  }
  if (w == INT || w == DOUBLE || w == CHAR || w == LONG || w == SHORT || w == FLOAT)
    root->r = LocalVarDefList();
  return root;
}

ASTTree *StateList()
//处理语句序列
{
  if (error)
    return NULL;
  ASTTree *root = NULL;
  ASTTree *root1 = Statement();
  if (!root1)
    return NULL;
  else
  {
    root = init_AST();
    root->type = STATELIST;
    root->l = root1;

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != RB)
    {
      root->r = StateList();
    }
    return root;
  }
}

ASTTree *Statement()
//处理语句
{
  if (error)
    return NULL;
  ASTTree *root = init_AST();
  switch (w)
  {
  case IF:
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != LP)
    {
      printf("Error in line %d\n", lines);
      printf("Error: Wrong IF statement\n");
      exit(0);
    }
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    ASTTree *p = init_AST();
    p->type = IFPART;
    p->l = Expression(RP);
    if (!p->l)
    {
      printf("Error in line %d\n", lines);
      printf("Error: ifStatement Condition\n");
      exit(0);
    }
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w == LB)
    {
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
      p->r = Statement();
    }
    else if (w == ARRAY || w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT || w == IF || w == WHILE || w == FOR || w == DO)
    {
      p->r = Statement();
    }
    else
    {
      printf("Error in line %d\n", lines);
      printf("Error: error in if\n");
      exit(0);
    }
    root->l = p;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w == ELSE)
    {
      root->type = IFELSESTATEMENT;
      ASTTree *q = init_AST();
      q->type = ELSEPART;
      root->r = q;
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
      if (w == LB)
      {
        w = getToken(fp);
        while (w == ANNO)
          w = getToken(fp);
        q->r = StateList();
      }
      else if (w == ARRAY || w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT || w == WHILE || w == FOR || w == DO)
      {
        q->r = Statement();
      }
      else if (w == IF)
      {
        q->l = Statement();
      }
      else
      {
        printf("Error in line %d\n", lines);
        printf("Error: error in else\n");
        exit(0);
      }
    }
    else
    {
      root->type = IFSTATEMENT;
      returnToken(fp);
    }
    return root;
    break;
  case WHILE:
    isInRecycle = 1;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);

    if (w != LP)
    {
      printf("Error in line %d\n", lines);
      printf("Error: Error in WHILE\n");
      exit(0);
    }

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);

    ASTTree *p = init_AST();
    p->type = WHILEPART;
    p->l = Expression(RP);
    if (!p->l)
    {
      printf("Error in line %d\n", lines);
      printf("Error: while Statement Condition\n");
      exit(0);
    }
    ASTTree *q = init_AST();
    q->type = WHILEBODY;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w == LB)
    {
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
      q->r = StateList();
    }
    else if (w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT)
    {
      q->r = Statement();
    }
    else
    {
      printf("Error in line %d\n", lines);
      printf("Error: Error in WHILE\n");
      exit(0);
    }
    root->type = WHILESTATEMENT;
    root->l = p;
    root->r = q;
    isInRecycle = 0;
    return root;
    break;
  default:
    break;
  }
}
void returnToken(FILE *fp)
{
  int len = strlen(token_text);
  for (int i = 0; i < len; i++)
  {
    ungetc(token_text[len - i - 1], fp);
  }
}
int can(char *name)
    //检测变量名字是否存在
    {
#error wait to finish
    } ASTTree *init_AST()
{
  ASTTree *root = (ASTTree *)malloc(sizeof(ASTTree));
  root->l = root->r = NULL;
  strcpy(root->data.data, NULL);
  root->type = root->data.type = 0;
  return root;
}
