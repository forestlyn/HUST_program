#include "format.h"

extern FILE *fp;
int tab = 0;
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
    print_tab();
    printf("%s", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case EXTVAR:
    printf(" %s", root->data.data);
    if (root->r)
    {
      printf(",");
    }
    else
      printf(";\n");
    print(root->r);
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
    print(root->r);
    printf(")");
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
    print(root->l);
    print(root->r);
    break;
  case FUNCBODY:
    printf("{");
    print(root->l);
    print(root->r);
    printf("}");
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
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case LOCALVARNAMELIST:
    print(root->l);
    print(root->r);
    break;
  case LOCALVARNAME:
    printf("%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case STATELIST:
    print(root->l);
    print(root->r);
    break;
  case EXPRESSION:
    midpre(root);
    break;
  case IFPART:
    printf("if (");
    print(root->l);
    printf(")\n{");
    print(root->r);
    break;
  case ELSEPART:
    printf("else ");
    if (root->r)
      printf("\n{");
    print(root->r);
    print(root->l);
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
    printf(")\n{");
    print(root->r);
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
    print(root->r);
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
  case FORPART3:
    print(root->l);
    print(root->r);
    break;
  case FORBODY:
    printf("\n{");
    print(root->l);
    print(root->r);
    break;
  case RETURNSTATEMENT:
    printf("\n{");
    print(root->l);
    print(root->r);
    break;
  default:
    break;
  }
}
void midpre(ASTTree *root)
{
  if (!root)
    return;
  midpre(root->l);
  printf("%s", root->data.data);
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
}
