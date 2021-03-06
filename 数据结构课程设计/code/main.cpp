#include "format.cpp"
FILE *fp;
char *fileName;
int main(int argc, char *argv[])
{
  if (argc != 2)
    return -1;
  char *finename = argv[1];
  int op = 1;
  while (op)
  {
    printf("\t1.lexicalAnalyse\n");
    printf("\t2.syntaxAnalyse\n");
    printf("\t3.format\n");
    printf("\t0.exit\n");
    printf("\tchoose in [0-3]:");
    scanf("%d", &op);
    init();
    switch (op)
    {
    case 1:
      fp = fopen(finename, "r");
      lexicalAnalyse();
      system("pause");
      break;
    case 2:
      fp = fopen(finename, "r");
      syntaxAnalyse();
      system("pause");
      break;
    case 3:
      fp = fopen(finename, "r");
      format();
      system("pause");
    default:
      break;
    }
  }
  return 0;
}
