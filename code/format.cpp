#include "format.h"

extern FILE *fp;
int tab = 0;
int root_type;
FILE *fp1;
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
    fprintf(fp1, "%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case EXTVARLIST:
    print(root->l);
    if (root->r)
    {
      fprintf(fp1, ", ");
      print(root->r);
    }
    else
      fprintf(fp1, ";\n");
    break;
  case EXTVAR:
    fprintf(fp1, "%s", root->data.data);
    break;
  case FUNCDEF:
    print(root->l);
    print(root->r);
    break;
  case FUNCRETURNTYPE:
    fprintf(fp1, "%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case FUNCNAME:
    fprintf(fp1, "%s(", root->data.data);
    if (root_type != FUNCCLAIM && !root->l)
      fprintf(fp1, ")\n");
    print(root->l);
    print(root->r);
    if (root_type == FUNCCLAIM && !root->l && !root->r)
      fprintf(fp1, ");\n");
    break;
  case FUNCFORMALPARALIST:
    print(root->l);
    if (root->r)
    {
      fprintf(fp1, ", ");
      print(root->r);
    }
    else if (root_type == FUNCCLAIM)
      fprintf(fp1, ");\n");
    else
      fprintf(fp1, ")\n");
    root_type = 0;
    break;
  case FUNCFORMALPARADEF:
    print(root->l);
    print(root->r);
    break;
  case FUNCFORMALPARATYPE:
    fprintf(fp1, "%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case FUNCFORMALPARA:
    fprintf(fp1, "%s", root->data.data);
    if (root->l)
    {
      fprintf(fp1, ", ");
      print(root->l);
    }
    break;
  case FUNCBODY:
    fprintf(fp1, "{\n");
    tab += 2;
    print(root->l);
    print(root->r);
    tab -= 2;
    fprintf(fp1, "}\n");
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
    fprintf(fp1, "%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case LOCALVARNAMELIST:
    print(root->l);
    if (root->r)
    {
      fprintf(fp1, ", ");
      print(root->r);
    }
    else
      fprintf(fp1, ";\n");
    break;
  case LOCALVARNAME:
    fprintf(fp1, "%s", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case STATELIST:
    print_tab();
    print(root->l);
    print(root->r);
    break;
  case EXPRESSION:
  {
    if (root_type == RETURNSTATEMENT ||
        root_type == FORPART1 || root_type == FORPART2 || root_type == FORPART3 ||
        root_type == FORPART || root_type == IFPART || root_type == WHILEPART ||
        root_type == DOWHILECONDITION)
    {
      ;
    }
    else
      root_type = EXPRESSION;
    midpre(root);
    switch (root_type)
    {
    case RETURNSTATEMENT:
    case CONTINUESTATEMENT:
    case EXPRESSION:
      fprintf(fp1, ";\n");
      break;
    case FORPART1:
    case FORPART2:
      fprintf(fp1, ";");
      break;
    }
    root_type = 0;
    break;
  }
  case IFPART:
    root_type = root->type;
    fprintf(fp1, "if (");
    print(root->l);
    fprintf(fp1, ")\n");
    print_tab();
    fprintf(fp1, "{\n");
    tab += 2;
    if (root->r->type != STATELIST)
      print_tab();
    print(root->r);
    tab -= 2;
    print_tab();
    fprintf(fp1, "}\n");
    break;
  case ELSEPART:
    root_type = root->type;
    print_tab();
    fprintf(fp1, "else ");
    if (root->r)
    {
      fprintf(fp1, "\n");
      print_tab();
      tab += 2;
      fprintf(fp1, "{\n");
    }
    print(root->l);
    if (root->l && root->l->type != IFSTATEMENT && root->l->type != IFELSESTATEMENT)
    {
      fprintf(fp1, "\n}\n");
    }
    print(root->r);
    if (!root->l)
    {
      tab -= 2;
      print_tab();
      fprintf(fp1, "}\n");
    }
    break;
  case IFSTATEMENT:
    root_type = root->type;
    print(root->l);
    print(root->r);
    break;
  case IFELSESTATEMENT:
    root_type = root->type;
    print(root->l);
    print(root->r);
    break;
  case WHILESTATEMENT:
    root_type = root->type;
    fprintf(fp1, "while (");
    print(root->l);
    fprintf(fp1, ")\n");
    print_tab();
    fprintf(fp1, "{\n");
    tab += 2;
    print(root->r);
    tab -= 2;
    print_tab();
    fprintf(fp1, "}\n");
    break;
  case WHILEPART:
    root_type = root->type;
    print(root->l);
    print(root->r);
    break;
  case WHILEBODY:
    root_type = root->type;
    print(root->l);
    print(root->r);
    break;
  case FORSTATEMENT:
    root_type = root->type;
    fprintf(fp1, "for (");
    print(root->l);
    print(root->r);
    break;
  case FORPART:
    root_type = root->type;
    print(root->l);
    break;
  case FORPART1:
    root_type = root->type;
    print(root->l);
    if (!root->l)
      fprintf(fp1, ";");
    print(root->r);
    break;
  case FORPART2:
    root_type = root->type;
    print(root->l);
    if (!root->l)
      fprintf(fp1, ";");
    print(root->r);
    break;
  case FORPART3:
    root_type = root->type;
    print(root->l);
    fprintf(fp1, ")\n");
    break;
  case FORBODY:
    root_type = root->type;
    print_tab();
    fprintf(fp1, "{\n");
    tab += 2;
    print(root->l);
    print(root->r);
    tab -= 2;
    print_tab();
    fprintf(fp1, "}\n");
    break;
  case RETURNSTATEMENT:
    root_type = root->type;
    if (root->r)
      fprintf(fp1, "return ");
    else
      fprintf(fp1, "return;\n");
    print(root->r);
    break;
  case BREAKSTATEMENT:
    root_type = root->type;
    fprintf(fp1, "break;\n");
    break;
  case DOWHILESTATEMENT:
    root_type = root->type;
    fprintf(fp1, "do\n");
    print_tab();
    fprintf(fp1, "{\n");
    tab += 2;
    print(root->l);
    tab -= 2;
    print_tab();
    fprintf(fp1, "} ");
    print(root->r);
    break;
  case DOWHILEBODY:
    root_type = root->type;
    print(root->l);
    print(root->r);
    break;
  case DOWHILECONDITION:
    root_type = root->type;
    fprintf(fp1, "while (");
    print(root->l);
    fprintf(fp1, ");\n");
    break;
  case CONTINUESTATEMENT:
    root_type = root->type;
    fprintf(fp1, "continue;\n");
    break;
  case FUNCCLAIM:
    root_type = root->type;
    print(root->l);
    print(root->r);
    break;
  case ARRAYDEF:
    print(root->l);
    print(root->r);
    break;
  case ARRAYTYPE:
    fprintf(fp1, "%s ", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case ARRAYNAME:
    fprintf(fp1, "%s;\n", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case INCLUDELIST:
    print(root->l);
    print(root->r);
    break;
  case INCLUDENAME:
    fprintf(fp1, "%s\n", root->data.data);
    print(root->l);
    print(root->r);
    break;
  case FUNUSE:
    root_type = root->type;
    print(root->l);
    print(root->r);
    fprintf(fp1, ");\n");
    break;
  case MACROLIST:
    print(root->l);
    print(root->r);
    break;
  case MACRONAME:
    fprintf(fp1, "%s\n", root->data.data);
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
  if (root->type == OPERATOR)
    fprintf(fp1, "(");
  midpre(root->l);
  if (strcmp(root->data.data, ""))
  {
    if (root->type == OPERATOR)
      fprintf(fp1, " ");
    fprintf(fp1, "%s", root->data.data);
    if (root->type == OPERATOR)
      fprintf(fp1, " ");
  }
  midpre(root->r);
  if (root->type == OPERATOR)
    fprintf(fp1, ")");
}
void print_tab()
{
  for (int i = 0; i < tab; i++)
    fprintf(fp1, " ");
}
void format()
{
  ASTTree *root = program();
  fp1 = fopen("format.txt", "w");
  if (root == NULL || error == 1)
  {
    fprintf(fp1, "syntax error!\n");
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
