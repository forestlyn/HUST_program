#include "syntaxAnalyse.h"
#include "lexicalAnalyse.cpp"
using namespace std;

extern char token_text[50];
extern char string_num[50];
extern int lines;
extern FILE *fp;

int w, type; // token type
int error = 0;
VDN *Vroot;   // 变量链表根节点
Fun *funroot; //函数链表结点
ASTTree *var; //函数形参
int isVoid, hasReturn, isInRecycle = 0;
int isExt = 1; //表示外部变量

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
    PreorderTranverse(root, 0);
}

ASTTree *program()
//开始分析
{
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  Vroot = (VDN *)malloc(sizeof(VDN));
  memset(Vroot->type, 0, sizeof(Vroot->type));
  Vroot->size = 0;
  Vroot->next = NULL;
  funroot = (Fun *)malloc(sizeof(Fun));
  funroot->next = NULL;
  strcpy(funroot->name, "");
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
  while (w == ANNO)
    w = getToken(fp);
  root->r = ExtDefList();
  return root;
}

ASTTree *ExtDef()
//判断外部定义，判断是变量还是函数还是头文件，进而调用其它函数处理
{
  int a;
  if (error)
    return NULL;
  if (w == INCLUDE)
  {
    ASTTree *p = init_AST();
    p->type = INCLUDELIST;
    p->r = headFile();
    return p;
  }
  if (w == MACRO)
  {
    ASTTree *p = init_AST();
    p->type = MACROLIST;
    p->r = macroFile();
    return p;
  }
  if (w != INT && w != FLOAT && w != CHAR && w != LONG && w != SHORT && w != DOUBLE && w != VOID)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong external define 1\n");
    exit(0);
  }
  type = w;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w != IDENT && w != ARRAY)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong external define 2\n");
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
  {
    isExt = 0;
    isVoid = 0;
    hasReturn = 0;
    p = FuncDef();
    isExt = 1;
  }
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
  if (!can(token_text, isExt, ARRAY))
  {
    printf("Error in line %d\n", lines);
    printf("Error: can't define %s twice\n", token_text);
    exit(0);
  }
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
  if (!can(token_text, isExt, type))
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
      printf("Error: wrong external define 3\n");
      exit(0);
    }
    if (w == SEMI)
      return root;
    w = getToken(fp);
    if (w != IDENT)
    {
      printf("Error in line %d\n", lines);
      printf("Error: wrong external define 4\n");
      exit(0);
    }

    if (!can(token_text, isExt, type))
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
ASTTree *headFile()
{
  ASTTree *root = init_AST();
  root->type = INCLUDENAME;
  root->data.type = INCLUDE;
  strcpy(root->data.data, token_text);
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  ASTTree *root1 = root;
  while (w == INCLUDE)
  {
    ASTTree *p = init_AST();
    p->type = INCLUDELIST;
    ASTTree *q = init_AST();
    q->type = INCLUDENAME;
    q->data.type = INCLUDE;
    strcpy(q->data.data, token_text);
    p->l = q;
    root1->r = p;
    root1 = p;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
  }
  returnToken(fp);
  return root;
}
ASTTree *macroFile()
{
  ASTTree *root = init_AST();
  root->type = MACRONAME;
  root->data.type = MACRO;
  strcpy(root->data.data, token_text);
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  ASTTree *root1 = root;
  while (w == MACRO)
  {
    ASTTree *p = init_AST();
    p->type = MACROLIST;
    ASTTree *q = init_AST();
    q->type = MACRONAME;
    q->data.type = MACRO;
    strcpy(q->data.data, token_text);
    p->l = q;
    root1->r = p;
    root1 = p;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
  }
  returnToken(fp);
  return root;
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
  memset(lastVDN->next->type, 0, sizeof(lastVDN->next->type));

  lastVDN = lastVDN->next;
  lastVDN->next = NULL;
  lastVDN->size = 0;

  var = init_AST();
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
    Fun *function = funroot;
    while (function->next)
      function = function->next;
    function->next = (Fun *)malloc(sizeof(Fun));
    function->next->Vardef = var;
    var = NULL;
    function->next->type = p->data.type;
    strcpy(function->next->name, q->data.data);
    function->next->next = NULL;
    q->r = CompState();
  }
  else
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong function def\n");
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
    printf("Error: wrong function def\n");
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
    printf("Error: wrong  formparadef\n");
    exit(0);
  }
  type = w;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w != IDENT)
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong  formparadef\n");
    exit(0);
  }
  ASTTree *root, *p;
  root = init_AST();
  p = init_AST();
  root->type = FUNCFORMALPARADEF;
  p->type = FUNCFORMALPARATYPE;
  p->data.type = type;

  ASTTree *var1 = var;
  while (var1->l)
    var1 = var1->l;
  var1->l = init_AST();
  var1->l->type = type;

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

  if (!can(token_text, isExt, type))
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
  root->type = FUNCBODY;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);

  if (w == INT || w == DOUBLE || w == CHAR || w == LONG || w == SHORT || w == FLOAT)
    root->l = LocalVarDefList();
  root->r = StateList(RB);
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
  type = w;
  if (w == INT)
    strcpy(q->data.data, "int");
  if (w == FLOAT)
    strcpy(q->data.data, "float");
  if (w == CHAR)
    strcpy(q->data.data, "char");
  if (w == LONG)
    strcpy(q->data.data, "long");
  if (w == SHORT)
    strcpy(q->data.data, "short");
  if (w == DOUBLE)
    strcpy(q->data.data, "double");
  if (w == ARRAY)
    strcpy(q->data.data, "array");

  p->l = q;
  p = q;

  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  q = init_AST();
  q->type = LOCALVARNAMELIST;
  p->r = q;

  if (w != IDENT && w != ARRAY)
  {
    printf("Error in line %d\n", lines);
    printf("Error: error in local vardef\n");
    exit(0);
  }
  p = q;
  if (!can(token_text, isExt, type))
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

      if (w != IDENT && w != ARRAY)
      {
        printf("Error in line %d\n", lines);
        printf("Error: error in local vardef\n");
        exit(0);
      }
      else if (!can(token_text, isExt, type))
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
  if (w == ARRAY || w == INT || w == DOUBLE || w == CHAR || w == LONG || w == SHORT || w == FLOAT)
    root->r = LocalVarDefList();
  return root;
}

ASTTree *StateList(int end)
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
    if (end == RB)
    {
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
    }
    if (w != end)
    {
      root->r = StateList(end);
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
  {
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
      p->r = StateList(RB);
    }
    else if (w == ARRAY || w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT || w == IF || w == WHILE || w == FOR || w == DO)
    {
      p->r = StateList(SEMI);
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
        q->r = StateList(RB);
      }
      else if (w == ARRAY || w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT || w == WHILE || w == FOR || w == DO)
      {
        q->r = StateList(SEMI);
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
  }
  case WHILE:
  {
    isInRecycle ++;
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
      q->r = StateList(RB);
    }
    else if (w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT || w == ARRAY || w == WHILE || w == IF || w == FOR || w == DO)
    {
      q->r = StateList(SEMI);
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
    isInRecycle --;
    return root;
    break;
  }
  case FOR:
  {
    isInRecycle ++;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != LP)
    {
      printf("Error in line %d\n", lines);
      printf("Error: Error in for condition\n");
      exit(0);
    }

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    ASTTree *p = init_AST();
    p->type = FORPART;
    ASTTree *q = init_AST();
    q->type = FORPART1;
    ASTTree *q1 = Expression(SEMI);
    p->l = q;
    q->l = q1;
    q1 = q;

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    q = init_AST();
    q->type = FORPART2;
    q1->r = q;
    q1 = Expression(SEMI);
    q->l = q1;
    q1 = q;

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    q = init_AST();
    q->type = FORPART3;
    q1->r = q;
    q1 = Expression(RP);
    q->l = q1;

    ASTTree *q2 = init_AST();
    q2->type = FORBODY;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w == LB)
    {
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
      q2->r = StateList(RB);
    }
    else if (w == ARRAY || w == INT_CONST || w == FLOAT_CONST || w == CHAR_CONST || w == IDENT || w == IF || w == WHILE || w == FOR || w == DO)
      q2->r = StateList(SEMI);
    else
    {
      printf("Error in line %d\n", lines);
      printf("Error: error in for\n");
      exit(0);
    }
    root->type = FORSTATEMENT;
    root->l = p;
    root->r = q2;
    isInRecycle --;
    return root;
    break;
  }
  case RETURN:
  {
    hasReturn = 1;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (isVoid && w != SEMI)
    {
      printf("Error in line %d\n", lines);
      printf("Error: void shouldn't have return statement\n");
      exit(0);
    }
    returnToken(fp);
    root->type = RETURNSTATEMENT;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    root->r = Expression(SEMI);
    return root;
    break;
  }
  case DO:
  {
    isInRecycle ++;
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != LB)
    {
      printf("Error in line %d\n", lines);
      printf("Error: error in do, miss {\n");
      exit(0);
    }
    ASTTree *p = init_AST();
    p->type = DOWHILEBODY;
    ASTTree *q = init_AST();
    q->type = DOWHILECONDITION;

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    p->l = StateList(RB);

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != WHILE)
    {
      printf("Error in line %d\n", lines);
      printf("Error: miss while in do-while\n");
      exit(0);
    }

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != LP)
    {
      printf("Error in line %d\n", lines);
      printf("Error: miss while LP in do-while\n");
      exit(0);
    }
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    q->l = Expression(RP);
    if (!q->l)
    {
      printf("Error in line %d\n", lines);
      printf("Error: miss while condition LP in do-while\n");
      exit(0);
    }

    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != SEMI)
    {
      printf("Error in line %d\n", lines);
      printf("Error: miss while SEMI in do-while\n");
      exit(0);
    }
    root->l = p;
    root->r = q;
    root->type = DOWHILESTATEMENT;
    isInRecycle--;
    return root;
    break;
  }
  case BREAK:
  {
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != SEMI)
    {
      printf("Error in line %d\n", lines);
      printf("Error: miss SEMI\n");
      exit(0);
    }
    if (!isInRecycle)
    {
      printf("Error in line %d\n", lines);
      printf("Error: unexpected break\n");
      exit(0);
    }
    root->type = BREAKSTATEMENT;
    return root;
    break;
  }
  case CONTINUE:
  {
    strcpy(root->data.data, token_text);
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w != SEMI)
    {
      printf("Error in line %d\n", lines);
      printf("Error: miss SEMI\n");
      exit(0);
    }
    if (!isInRecycle)
    {
      printf("Error in line %d\n", lines);
      printf("Error: unexpected continue\n");
      exit(0);
    }
    root->type = CONTINUESTATEMENT;
    return root;
    break;
  }
  case IDENT:
  {
    Fun *f = checkFun(token_text);
    if (f)
    {
      return FunUse(f);
    }
    else
      return Expression(SEMI);
  }
  case INT_CONST:
  case FLOAT_CONST:
  case CHAR_CONST:
  case LONG_CONST:
  case STRING_CONST:
  case ARRAY:
    return Expression(SEMI);
    break;
  default:
    return root;
    break;
  }
}
ASTTree *Expression(int end)
{
  if (error || w == end)
    return NULL;

  int errors = 0;
  stack<ASTTree *> op; //运算符号
  ASTTree *p = init_AST();
  p->type = OPERATOR;
  p->data.type = POUND;
  op.push(p);
  stack<ASTTree *> opn; //运算数
  ASTTree *p1, *p2, *root;
  while (((w != end) || (op.top()->data.type != POUND)) && !errors)
  {
    if (op.top()->data.type == RP)
    {
      if (op.size() < 3)
      {
        errors++;
        break;
      }
      op.pop();
      op.pop();
    }
    if (w == IDENT)
    {
      if (!checkName(token_text, 0))
      {
        printf("Error in line %d\n", lines);
        printf("Error: don't exit %s\n", token_text);
        exit(0);
      }
    }
    if (w == IDENT || w == INT_CONST || w == FLOAT_CONST || w == LONG_CONST || w == CHAR_CONST || w == ARRAY || w == STRING_CONST)
    {
      p = init_AST();
      p->type = OPERAND;
      strcpy(p->data.data, token_text);
      opn.push(p);
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
    }
    else if (w == end)
    {
      while (op.top()->data.type != POUND)
      {
        p2 = opn.top();
        if (!p2)
        {
          errors++;
          break;
        }
        if (p2)
          opn.pop();
        if (!opn.size())
          p1 = NULL;
        else
          p1 = opn.top();
        if (!p1)
        {
          errors++;
          break;
        }
        if (p1)
          opn.pop();
        p = op.top();
        if (!p)
        {
          errors++;
          break;
        }
        else
          op.pop();
        p->l = p1;
        p->r = p2;
        opn.push(p);
      }
      if (opn.size() != 1)
        errors++;
    }
    else if (w >= EQ && w <= OROR)
    //推入运算符，要比较优先级
    {
      switch (Precede(op.top()->data.type, w))
      {
      case '<':
        p = init_AST();
        p->type = OPERATOR;
        p->data.type = w;
        strcpy(p->data.data, token_text);
        op.push(p);
        w = getToken(fp);
        while (w == ANNO)
          w = getToken(fp);
        break;
      case '>':
        p2 = opn.top();
        if (p2)
          opn.pop();
        if (!opn.size())
        {
          errors++;
          break;
        }
        p1 = opn.top();
        if (p1)
          opn.pop();
        p = op.top();
        if (!p)
        {
          errors++;
          break;
        }
        op.pop();
        p->l = p1;
        p->r = p2;
        opn.push(p);

        p = init_AST();
        p->type = OPERATOR;
        p->data.type = w;
        strcpy(p->data.data, token_text);
        op.push(p);

        w = getToken(fp);
        while (w == ANNO)
          w = getToken(fp);
        break;
      case '=':
        p = op.top();
        if (!p)
        {
          errors++;
          break;
        }
        w = getToken(fp);
        while (w == ANNO)
          w = getToken(fp);
        break;
      case '\0':
        printf("Error in line %d\n", lines);
        printf("Error: unknown operator\n");
        exit(0);
      }
    }
    else
      error = 1;
  }
  if ((opn.size() == 1) && (op.top()->data.type == POUND) && !error)
  {
    p = opn.top();
    opn.pop();
    root = init_AST();
    root->type = EXPRESSION;
    root->l = p;
    return root;
  }
  else
  {
    printf("Error in line %d\n", lines);
    printf("Error: wrong expression\n");
    exit(0);
  }
}
char Precede(int a, int b)
//运算符优先级比较
{
  if (error == 1)
    return NULL;
  if (a == PLUS || a == MINUS)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case RP:
    case POUND:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case EQ:
    case NEQ:
    case ASSIGN:
    case ANDAND:
    case OROR:
      return '>';
    case TIMES:
    case DIVIDE:
    case LP:
      return '<';
    default:
      return '\0';
      break;
    }
  }
  else if (a == TIMES || a == DIVIDE)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case RP:
    case POUND:
    case TIMES:
    case DIVIDE:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case EQ:
    case NEQ:
    case ANDAND:
    case OROR:
      return '>';
    case LP:
      return '<';
    default:
      return '\0';
    }
  }
  else if (a == LP)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
    case ANDAND:
    case OROR:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case EQ:
    case NEQ:
      return '<';
    case RP:
      return '=';

    case POUND:
      return '>';
    default:
      return '\0';
    }
  }
  else if (a == RP)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case EQ:
    case POUND:
    case ANDAND:
    case OROR:
      return '>';
    default:
      return '\0';
    }
  }
  else if (a == ASSIGN)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case EQ:
    case NEQ:
    case ANDAND:
    case OROR:
      return '<';
    case POUND:
      return '>';
    default:
      return '\0';
    }
  }
  else if (a == MORE || a == LESS || a == MOREEQUAL || a == LESSEQUAL)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
      return '<';
    case RP:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case EQ:
    case NEQ:
    case POUND:
    case ANDAND:
    case OROR:
      return '>';
    default:
      return '\0';
    }
  }
  else if (a == EQ || a == NEQ)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case ANDAND:
    case OROR:
      return '<';
    case RP:
    case EQ:
    case NEQ:
    case POUND:
      return '>';
    default:
      return '\0';
    }
  }
  else if (a == POUND)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case RP:
    case EQ:
    case NEQ:
    case ASSIGN:
    case ANDAND:
    case OROR:
      return '<';
    case POUND:
      return '=';
    default:
      return '\0';
    }
  }
  else if (a == ANDAND || a == OROR)
  {
    switch (b)
    {
    case PLUS:
    case MINUS:
    case TIMES:
    case DIVIDE:
    case LP:
    case MORE:
    case LESS:
    case MOREEQUAL:
    case LESSEQUAL:
    case RP:
    case EQ:
    case NEQ:
      return '<';
    case ANDAND:
    case OROR:
    case ASSIGN:
    case POUND:
      return '>';
    default:
      return '\0';
    }
  }
  return '\0';
}
void returnToken(FILE *fp)
{
  int len = strlen(token_text);
  for (int i = 0; i < len; i++)
  {
    ungetc(token_text[len - i - 1], fp);
  }
}
int can(char *name, int flag_, int type)
//检测变量名字是否存在并加入，flag_=1表示是外部变量
{
  if (error)
    return NULL;
  int i, flag = 0;
  VDN *p = Vroot;
  if (!flag_)
    while (p->next)
      p = p->next;
  for (i = 0; i < (p->size); i++)
  {
    if (!strcmp(p->variable[i], name))
    {
      flag = 1;
      break;
    }
  }
  if (flag == 1)
  {
    error = 1;
    return 0;
  }
  else
  {
    p->type[p->size] = type;
    strcpy(p->variable[p->size], name);
    p->size++;
    return 1;
  }
}
int checkName(char *name, int type)
{
  if (error)
    return NULL;
  int i, flag = 0;
  VDN *p = Vroot;
  while (p->next)
    p = p->next;
  for (i = 0; i < p->size; i++)
  {
    if (!strcmp(p->variable[i], name))
    {
      if (!type)
      {
        flag = 1;
        break;
      }
      else if (type == p->type[i])
      {
        flag = 1;
        break;
      }
      //else
      //printf("\ncheck!:%s %d %d\n", p->variable[i], p->type[i], type);
    }
  }
  for (i = 0; i < Vroot->size; i++)
  {
    if (!strcmp(Vroot->variable[i], name))
    {
      if (!type)
      {
        flag = 1;
        break;
      }
      else if (type == Vroot->type[i])
      {
        flag = 1;
        break;
      }
    }
  }
  if (!flag)
  {
    error = 1;
    return 0;
  }
  return 1;
}
ASTTree *init_AST()
{
  ASTTree *root = (ASTTree *)malloc(sizeof(ASTTree));
  root->l = root->r = NULL;
  strcpy(root->data.data, "");
  root->type = root->data.type = 0;
  return root;
}
int checkType(int a, int b)
{
  if (a == INT_CONST && b == INT)
    return 1;
  if (a == FLOAT_CONST && b == FLOAT)
    return 1;
  if (a == CHAR_CONST && b == CHAR)
    return 1;
  if (a == LONG_CONST && b == LONG)
    return 1;
  return 0;
}
Fun *checkFun(char *name)
{
  Fun *f = funroot;
  while (f)
  {
    if (!strcmp(f->name, name))
    {
      return f;
    }
    f = f->next;
  }
  return NULL;
}

ASTTree *FunUse(Fun *f)
{
  ASTTree *root = init_AST();
  root->type = FUNUSE;
  ASTTree *p = init_AST();
  p->type = FUNCNAME;
  strcpy(p->data.data, token_text);
  root->l = p;
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w != LP)
  {
    printf("Error in line %d\n", lines);
    printf("ERROR: error in funuse,lose (\n");
    exit(0);
  }
  w = getToken(fp);
  while (w == ANNO)
    w = getToken(fp);
  if (w == RP && !f->Vardef->l)
  {
    w = getToken(fp);
    while (w == ANNO)
      w = getToken(fp);
    if (w == SEMI)
      return root;
    else
    {
      printf("Error in line %d\n", lines);
      printf("ERROR: error in funuse, miss ;3\n");
      exit(0);
    }
  }
  if ((w == IDENT || w == INT_CONST || w == FLOAT_CONST || w == LONG_CONST || w == CHAR_CONST) && f->Vardef->l)
  {
    ASTTree *q;
    ASTTree *var = f->Vardef;
    var = var->l;
    //printf("check:%d", checkName(token_text, var->type));
    while (var && ((w == IDENT && checkName(token_text, var->type)) || ((w == INT_CONST || w == FLOAT_CONST || w == LONG_CONST || w == CHAR_CONST) && checkType(w, var->type))))
    {
      q = init_AST();
      q->type = FUNCFORMALPARA;
      strcpy(q->data.data, token_text);
      p->l = q;
      p = q;
      var = var->l;
      w = getToken(fp);
      while (w == ANNO)
        w = getToken(fp);
      if (var && w != COMMA)
      {
        printf("Error in line %d\n", lines);
        printf("ERROR: error in funuse, miss ,1\n");
        exit(0);
      }
      else if (var)
      {
        w = getToken(fp);
        while (w == ANNO)
          w = getToken(fp);
      }
    }
    if (!var && w != IDENT)
    {
      if (w == RP)
      {
        w = getToken(fp);
        while (w == ANNO)
          w = getToken(fp);
        if (w == SEMI)
          return root;
        else
        {
          printf("Error in line %d\n", lines);
          printf("ERROR: error in funuse, miss ;2\n");
          exit(0);
        }
      }
      else
      {
        printf("Error in line %d\n", lines);
        printf("ERROR: error in funuse,lose )\n");
        exit(0);
      }
    }
    else
    {
      printf("Error in line %d\n", lines);
      printf("ERROR: error in funuse,var\n");
      exit(0);
    }
  }
  else
  {
    printf("Error in line %d\n", lines);
    printf("ERROR: error in funuse\n");
    exit(0);
  }
}

void PreorderTranverse(ASTTree *root, int depth)
{
  if (!root)
    printf("  ");
  else
  {
    int i;
    for (i = 0; i < depth; i++)
      printf("  ");
    showType(root->type);
    if (strcmp(root->data.data, ""))
    {
      for (i = 0; i < depth; i++)
        printf("  ");
      printf("%s\n", root->data.data);
    }
    PreorderTranverse(root->l, depth + 1);
    PreorderTranverse(root->r, depth + 1);
  }
}
void showType(int type)
{
  switch (type)
  {
  case 1:
    printf("外部序列\n");
    break;
  case 2:
    printf("外部变量序列\n");
    break;
  case 3:
    printf("外部变量种类\n");
    break;
  case 4:
    printf("外部变量名字序列\n");
    break;
  case 5:
    printf("外部变量名字\n");
    break;
  case 6:
    printf("函数定义\n");
    break;
  case 7:
    printf("函数返回值类型\n");
    break;
  case 8:
    printf("函数名\n");
    break;
  case 9:
    printf("函数形式参数序列\n");
    break;
  case 10:
    printf("函数形式参数\n");
    break;
  case 11:
    printf("函数形参类型\n");
    break;
  case 12:
    printf("函数形参名\n");
    break;
  case 13:
    printf("函数体\n");
    break;
  case 14:
    printf("局部变量定义序列\n");
    break;
  case 15:
    printf("局部变量定义\n");
    break;
  case 16:
    printf("局部变量类型\n");
    break;
  case 17:
    printf("局部变量名序列\n");
    break;
  case 18:
    printf("局部变量名\n");
    break;
  case 19:
    printf("语句序列\n");
    break;
  case 20:
    printf("操作数\n");
    break;
  case 21:
    printf("运算符\n");
    break;
  case 22:
    printf("表达式\n");
    break;
  case 23:
    printf("if语句部分\n");
    break;
  case 24:
    printf("else语句\n");
    break;
  case 25:
    printf("if语句\n");
    break;
  case 26:
    printf("if-else语句\n");
    break;
  case 27:
    printf("if-else语句\n");
    break;
  case 28:
    printf("while条件语句\n");
    break;
  case 29:
    printf("while语句体\n");
    break;
  case 30:
    printf("for语句\n");
    break;
  case 31:
    printf("for条件语句\n");
    break;
  case 32:
    printf("for语句条件一\n");
    break;
  case 33:
    printf("for语句条件二\n");
    break;
  case 34:
    printf("for语句条件三\n");
    break;
  case 35:
    printf("for语句体\n");
    break;
  case 36:
    printf("return语句\n");
    break;
  case 37:
    printf("break语句\n");
    break;
  case 38:
    printf("do-while循环语句\n");
    break;
  case 39:
    printf("do-while语句体\n");
    break;
  case 40:
    printf("do-while条件\n");
    break;
  case 41:
    printf("continue语句\n");
    break;
  case 42:
    printf("函数声明\n");
    break;
  case 43:
    printf("数组定义\n");
    break;
  case 44:
    printf("数组类型\n");
    break;
  case 45:
    printf("数组名\n");
    break;
  case 46:
    printf("数组大小\n");
    break;
  case 47:
    printf("头文件序列\n");
    break;
  case 48:
    printf("头文件名字\n");
    break;
  case 49:
    printf("函数调用\n");
    break;
  case 50:
    printf("宏定义序列\n");
    break;
  case 51:
    printf("宏定义名字\n");
    break;
  default:
    printf("no type\n");
    break;
  }
}
