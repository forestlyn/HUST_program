#include "format.h"


extern FILE *fp;
void print(ASTTree *root)
{
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
