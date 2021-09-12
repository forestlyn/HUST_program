#include "format.h"

extern FILE *fp;
int tab = 0;
int flag = 0, semi = 0, inBlock = 0;
void print(ASTTree *root)
{
  if (!root)
    return;
  switch (root->type)
  {
  case EXTDEFLIST:
    print(root->l);
    print(root->r);
    break;
  case EXTVARDEF:
    print(root->l);
    print(root->r);
    break;
  case EXTVARTYPE:
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case EXTVARLIST:
    print(root->l);
    if (root->r)
    {
      printf(", ");
      print(root->r);
    }
    else
      printf(";\n");
    break;
  case EXTVAR:
    printf("%s", root->data.data);
    break;
  case FUNCDEF:
    print(root->l);
    print(root->r);
    break;
  case FUNCRETURNTYPE:
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case FUNCNAME:
    printf("%s(", root->data.data);
    if (!root->l)
      printf(");\n");
    print(root->l);
    print(root->r);
    break;
  case FUNCFORMALPARALIST:
    print(root->l);
    if (root->r)
    {
      printf(", ");
      print(root->r);
    }
    else
      printf(")\n");
    break;
  case FUNCFORMALPARADEF:
    print(root->l);
    print(root->r);
    break;
  case FUNCFORMALPARATYPE:
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case FUNCFORMALPARA:
    printf("%s", root->data.data);
    if (root->l)
    {
      printf(", ");
      print(root->l);
    }
    break;
  case FUNCBODY:
    printf("{\n");
    tab += 2;
    print(root->l);
    print(root->r);
    tab -= 2;
    printf("}\n");
    break;
  case LOCALVARDEFLIST:
    print(root->l);
    print(root->r);
    break;
  case LOCALVARDEF:
    print(root->l);
    print(root->r);
    break;
  case LOCALVARTYPE:
    print_tab();
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case LOCALVARNAMELIST:
    print(root->l);
    if (root->r)
    {
      printf(", ");
      print(root->r);
    }
    else
      printf(";\n");
    break;
  case LOCALVARNAME:
    printf("%s", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case STATELIST:
    print_tab();
    print(root->l);
    if (root->r || semi)
      printf(";\n");
    print(root->r);
    if (!root->r && !root->l)
      printf(";\n");
    break;
  case EXPRESSION:
    midpre(root);
    flag = 0;
    break;
  case IFPART:
    printf("if (");
    print(root->l);
    printf(")\n");
    print_tab();
    printf("{\n");
    tab += 2;
    if (root->r->type != STATELIST)
      print_tab();
    print(root->r);
    tab -= 2;
    printf(";\n");
    print_tab();
    printf("}\n");
    break;
  case ELSEPART:
    print_tab();
    printf("else ");
    if (root->r)
      printf("\n{\n");
    print(root->l);
    if (root->l->type != IFSTATEMENT && root->l->type != IFELSESTATEMENT)
    {
      printf("\n}\n");
    }
    else
    {
      int t = tab;
      tab = 0;
      print(root->r);
      tab = t;
    }
    break;
  case IFSTATEMENT:
    print(root->l);
    print(root->r);
    break;
  case IFELSESTATEMENT:
    print(root->l);
    print(root->r);
    break;
  case WHILESTATEMENT:
    printf("while (");
    print(root->l);
    printf(")\n");
    print_tab();
    printf("{\n");
    tab += 2;
    print(root->r);
    tab -= 2;
    printf(";\n");
    print_tab();
    printf("}\n");
    break;
  case WHILEPART:
    print(root->l);
    print(root->r);
    break;
  case WHILEBODY:
    print(root->l);
    print(root->r);
    break;
  case FORSTATEMENT:
    printf("for (");
    print(root->l);
    print(root->r);
    break;
  case FORPART:
    print(root->l);
    break;
  case FORPART1:
    print(root->l);
    printf(";");
    print(root->r);
    break;
  case FORPART2:
    print(root->l);
    printf(";");
    print(root->r);
    break;
  case FORPART3:
    print(root->l);
    printf(")\n");
    print(root->r);
    break;
  case FORBODY:
    print_tab();
    printf("{\n");
    tab += 2;
    print(root->l);
    print(root->r);
    tab -= 2;
    printf(";\n");

    print_tab();
    printf("}\n");
    break;
  case RETURNSTATEMENT:
    printf("return ");
    print(root->r);
    break;
  case BREAKSTATEMENT:
    printf("break");
    break;
  case DOWHILESTATEMENT:
    printf("do\n");
    print_tab();
    printf("{\n");
    tab += 2;
    print(root->l);
    tab -= 2;
    printf(";\n");
    print_tab();
    printf("} ");
    print(root->r);
    break;
  case DOWHILEBODY:
    print(root->l);
    print(root->r);
    break;
  case DOWHILECONDITION:
    printf("while (");
    print(root->l);
    printf(");\n");
  case CONTINUESTATEMENT:
    printf("continue");
    break;
  case FUNCCLAIM:
    print(root->l);
    print(root->r);
    break;
  case ARRAYDEF:
    print(root->l);
    print(root->r);
    break;
  case ARRAYTYPE:
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case ARRAYNAME:
    printf("%s", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case INCLUDELIST:
    print(root->l);
    print(root->r);
    break;
  case INCLUDENAME:
    printf("%s\n", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case FUNUSE:
    print(root->l);
    print(root->r);
    printf(")");
    break;
  case MACROLIST:
    print(root->l);
    print(root->r);
    break;
  case MACRONAME:
    printf("%s\n", root->data.data);
    print(root->l);
    print(root->r);
  default:
    break;
  }
}
void midpre(ASTTree *root)
{
  if (!root)
    return;
  midpre(root->l);
  if (strcmp(root->data.data, ""))
  {
    if (flag)
      printf(" ");
    printf("%s", root->data.data);
    flag = 1;
  }
  midpre(root->r);
}
void print_tab()
{
  for (int i = 0; i < tab; i++)
    printf(" ");
}
void format()
{
  ASTTree *root = program();
  if (root == NULL || error == 1)
  {
    printf("syntax error!\n");
    return;
  }
  else
  {
    print(root);
  }
}

void init()
{
  lines = 1;
  error = 0;
  isExt = 1;
  Vroot = NULL;
  isInRecycle = 0;
  isVoid = 0;
  hasReturn = 0;
}
