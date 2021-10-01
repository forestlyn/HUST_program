#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define LISTS_INIT_SIZE 10
#define LISTSINCREMENT 10

typedef int status;
typedef int ElemType; //数据元素类型定义

typedef struct
{ //顺序表（顺序结构）的定义
  char name[30];
  ElemType *elem;
  int length;
  int listsize;
} SqList;
typedef struct
{ //线性表的管理表定义
  SqList *elem;
  int length;
  int listsSize;
} LISTS;

status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status CreateNewList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
status LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType e, ElemType &pre);
status NextElem(SqList L, ElemType e, ElemType &next);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList L);
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);
status AddList(LISTS &Lists, SqList L);
status InitLists(LISTS &Lists);
status ListsTraverse(LISTS Lists);
status LocateList(LISTS Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
status ReLists(LISTS &Lists);
int main()
{
  LISTS Lists;
  Lists.length = 0;
  Lists.listsSize = 10;
  Lists.elem = (SqList *)malloc(sizeof(SqList) * LISTS_INIT_SIZE);
  char filename1[30] = "LinkLists.txt";
  char filename2[30] = "Lists.txt";
  char Listname[30];
  ElemType i, e, pre, next, result;
  int op = 1, now = 0;
  while (op)
  {
    printf("The op of Lists\n");
    printf("1.AddList\n");
    printf("2.ListsTraverse\n");
    printf("3.LocateList\n");
    printf("4.RemoveList\n");
    printf("5.choose List\n");
    printf("0.exit\n");
    printf("-------------------------------------------------\n");
    printf("choose [0-5]:");
    scanf("%d", &op);
    while (op)
    {
      switch (op)
      {
      case 1:
        if (Lists.length == Lists.listsSize)
        {
          Lists.listsSize += LISTSINCREMENT;
          Lists.elem = (SqList *)realloc(Lists.elem, sizeof(SqList) * Lists.listsSize);
        }
        Lists.elem[Lists.length].elem = NULL;
        if (InitList(Lists.elem[Lists.length]) != OK)
          printf("ERROR!");
        int temp;
        printf("input the elem of list:");
        scanf("%d", &temp);
        while (temp)
        {
          ListInsert(Lists.elem[Lists.length], Lists.elem[Lists.length].length + 1, temp);
          scanf("%d", &temp);
        }
        now++;
        Lists.length++;
        break;
      case 2:
        ListsTraverse(Lists);
        break;
      case 3:
        printf("input the name of List:");
        scanf("%s", Listname);
        result = LocateList(Lists, Listname);
        if (result)
          printf("the List %s is the %dth List\n", Listname, result);
        else
          printf("ERROR!\n");
        break;
      case 4:
        printf("input the name of List:");
        scanf("%s", Listname);
        result = RemoveList(Lists, Listname);
        if (result)
          printf("Success!\n");
        else
          printf("ERROR!\n");
        break;
      case 5:
        printf("input the name of List:");
        scanf("%s", Listname);
        result = LocateList(Lists, Listname);
        if (result == 0)
        {
          printf("Don't exist!\n");
        }
        else
        {
          system("cls");
          now = result - 1;
          printf("      The List you choose is %s\n", Lists.elem[now].name);
          printf("      Menu for Linear Table On Sequence Structure \n");
          printf("-------------------------------------------------\n");
          printf("                The op of List\n");
          printf("    	  1. InitList       2. DestroyList\n");
          printf("    	  3. ClearList      4. ListEmpty\n");
          printf("    	  5. ListLength     6. GetElem \n");
          printf("    	  7. LocateElem     8. PriorElem\n");
          printf("    	  9. NextElem       10. ListInsert\n");
          printf("    	  11. ListDelete    12. ListTrabverse\n");
          printf("    	  13. SaveList      14.LoadList\n");
          printf("    	  0.exit   \n");
          printf("-------------------------------------------------\n");
          printf("choose [0-14]:");
          scanf("%d", &op);
          while (op >= 0)
          {
            switch (op)
            {
            case 1:
              //status InitList(LinkList &L)
              if (InitList(Lists.elem[now]) == OK)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 2:
              //status DestroyList(LinkList &L)
              if (DestroyList(Lists.elem[now]) == OK && Lists.elem[now].elem == NULL)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 3:
              //status ClearList(LinkList &L)
              if (ClearList(Lists.elem[now]) == OK)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 4:
              //status ListEmpty(LinkList L)
              result = ListEmpty(Lists.elem[now]);
              if (result == TRUE)
                printf("is Empty!\n");
              else if (result == FALSE)
                printf("isn't Empty!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 5:
              //status ListLength(LinkList L)
              result = ListLength(Lists.elem[now]);
              if (result != INFEASIBLE)
                printf("The length is %d\n", result);
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 6:
              //status GetElem(LinkList L, int i, ElemType &e)
              printf("please input the number i:\n");
              scanf("%d", &i);
              result = GetElem(Lists.elem[now], i, e);
              if (result == INFEASIBLE)
                printf("INFEASIBLE!\n");
              else if (result == ERROR)
                printf("Error!\n");
              else
                printf("The %dth number is %d\n", i, e);
              getchar();
              break;
            case 7:
              //status LocateElem(LinkList L, ElemType e)
              printf("please input the number e:\n");
              scanf("%d", &e);
              result = LocateElem(Lists.elem[now], e);
              if (result == INFEASIBLE)
                printf("INFEASIBLE\n");
              else if (result == ERROR)
                printf("Error!\n");
              else
                printf("the elem %d is %dth!\n", e, result);
              getchar();
              break;
            case 8:
              //status PriorElem(LinkList L, ElemType e, ElemType &pre)
              printf("please input the number e:\n");
              scanf("%d", &e);
              result = PriorElem(Lists.elem[now], e, pre);
              if (result == INFEASIBLE)
                printf("INFEASIBLE\n");
              else if (result == ERROR)
                printf("Error!\n");
              else if (result == OK)
                printf("Success! The prior elem is %d!\n", pre);
              getchar();
              break;
            case 9:
              //status NextElem(LinkList L, ElemType e, ElemType &next)
              printf("please input the number e:\n");
              scanf("%d", &e);
              result = NextElem(Lists.elem[now], e, next);
              if (result == INFEASIBLE)
                printf("INFEASIBLE\n");
              else if (result == ERROR)
                printf("Error!\n");
              else if (result == OK)
                printf("Success! The next elem is %d!\n", next);
              getchar();
              break;
            case 10:
              //status ListInsert(LinkList &L, int i, ElemType e)
              printf("please input the number i, e:\n");
              scanf("%d%d", &i, &e);
              result = ListInsert(Lists.elem[now], i, e);
              if (result == INFEASIBLE)
                printf("INFEASIBLE\n");
              else if (result == ERROR)
                printf("Error!\n");
              else if (result == OK)
                printf("Success!\n");
              getchar();
              break;
            case 11:
              //status ListDelete(LinkList &L, int i, ElemType &e);
              printf("please input the number i:\n");
              scanf("%d", &i);
              result = ListDelete(Lists.elem[now], i, e);
              if (result == OK)
                printf("Success!\n");
              else if (result == INFEASIBLE)
                printf("INFEASIBLE\n");
              else if (result == ERROR)
                printf("Error!\n");
              getchar();
              break;
            case 12:
              //status ListTraverse(LinkList L);
              result = ListTraverse(Lists.elem[now]);
              if (result == OK)
                printf("");
              else if (result == INFEASIBLE)
                printf("INFEASIBLE\n");
              else if (result == ERROR)
                printf("Error!\n");
              getchar();
              break;
            case 13:
              //status SaveList(LinkList L, char FileName[])
              result = SaveList(Lists.elem[now], filename1);
              if (result == INFEASIBLE)
                printf("INFEASIBLE!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 14:
              //status LoadList(LinkList &L, char FileName[])
              result = LoadList(Lists.elem[now], filename1);
              if (result == INFEASIBLE)
                printf("INFEASIBLE!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            deufalt:
              break;
            }
            if (op == 0)
            {
              system("cls");
              printf("The op of Lists\n");
              printf("1.AddList\n");
              printf("2.ListsTraverse\n");
              printf("3.LocateList\n");
              printf("4.RemoveList\n");
              printf("5.choose List\n");
              printf("0.exit\n");
              printf("-------------------------------------------------\n");
              ReLists(Lists);
              op = -1;
              break;
            }
            printf("choose [0-14]:");
            scanf("%d", &op);
          }
        }
        break;
      case 0:
        printf("Welcome to use it next time!\n");
      default:
        break;
      }
      if (op == 0)
        return 0;
      printf("choose [0-5]:");
      scanf("%d", &op);
    }
  }
  return 0;
}

status InitList(SqList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
  //检查L是否存在
  if (L.elem)
  {
    return INFEASIBLE;
  }
  //不存在则构造一个空的线性表
  else
  {
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    printf("input the name of list:");
    scanf("%s", L.name);
  }
  return OK;
}

status DestroyList(SqList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
  //检查线性表L是否存在
  if (!L.elem)
    return INFEASIBLE;
  //销毁线性表L
  else
  {
    free(L.elem);
    L.length = L.listsize = 0;
    L.elem = NULL;
    L.name[0] = '\0';
  }
  return OK;
}

status ClearList(SqList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
  //检测L是否存在
  if (!L.elem)
    return INFEASIBLE;
  //长度置为0
  else
  {
    L.length = 0;
  }
  return OK;
}

status CreateNewList(SqList &L)
{
  SqList L1;
  L1.elem = NULL;
  L = L1;
  if (L.elem)
    return ERROR;
  return OK;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  else
  {
    if (L.length)
      return FALSE;
    return TRUE;
  }
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
  //判断线性表L是否存在
  if (!L.elem)
    return INFEASIBLE;
  return L.length;
}

status GetElem(SqList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  else if (i > L.length || i < 1)
    return ERROR;
  else
  {
    e = L.elem[i - 1];
  }
  return OK;
}

status LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  for (int i = 0; i < L.length; i++)
  {
    if (L.elem[i] == e)
      return i + 1;
  }
  return ERROR;
}

status PriorElem(SqList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  for (int i = 1; i < L.length; i++)
  {
    if (L.elem[i] == e)
    {
      pre = L.elem[i - 1];
      return OK;
    }
  }
  return ERROR;
}

status NextElem(SqList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  for (int i = 0; i < L.length - 1; i++)
  {
    if (L.elem[i] == e)
    {
      next = L.elem[i + 1];
      return OK;
    }
  }
  return ERROR;
}

status ListInsert(SqList &L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  //检测线性表L是否存在
  if (!L.elem)
    return INFEASIBLE;
  //检测插入位置是否正确
  else if (i < 1 || i > L.length + 1)
    return ERROR;
  //检测插入后是否会溢出
  else if (L.length == L.listsize)
  {
    L.elem = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
    L.listsize += LISTINCREMENT;
  }
  //插入
  ElemType t1, t2;
  t1 = e;
  L.length++;
  for (int j = i - 1; j < L.length; j++)
  {
    t2 = L.elem[j];
    L.elem[j] = t1;
    t1 = t2;
  }
  return OK;
}

status ListDelete(SqList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  //检查删除位置是否正确
  if (i < 1 || i > L.length)
    return ERROR;
  //进行删除操作
  e = L.elem[i - 1];
  L.length--;
  for (int j = i - 1; j < L.length; j++)
  {
    L.elem[j] = L.elem[j + 1];
  }
  return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  printf("%s    ", L.name);
  if (L.length == 0)
    printf("L.elem is Empty!\n");

  for (int i = 0; i < L.length; i++)
  {
    if (i != L.length - 1)
      printf("%d ", L.elem[i]);
    else
      printf("%d\n", L.elem[i]);
  }
  return OK;
}

status SaveList(SqList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
  if (!L.elem)
    return INFEASIBLE;
  FILE *fp = fopen(FileName, "w");
  putc(L.length, fp);
  putc(L.listsize, fp);
  fwrite(L.name, sizeof(char) * 30, 1, fp);
  fwrite(L.elem, sizeof(ElemType), L.length, fp);
  fclose(fp);
  return OK;
}

status LoadList(SqList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
  if (L.elem)
    return INFEASIBLE;
  FILE *fp = fopen(FileName, "r");
  L.length = getc(fp);
  L.listsize = getc(fp);
  L.elem = (ElemType *)malloc(L.listsize * sizeof(ElemType));
  fread(L.name, sizeof(char) * 30, 1, fp);
  fread(L.elem, sizeof(ElemType), L.length, fp);
  fclose(fp);
  return OK;
}

status AddList(LISTS &Lists, SqList L)
// 将当前线性表L加入到Lists中
{
  if (!L.elem)
    return INFEASIBLE;
  if (!Lists.elem)
    return INFEASIBLE;
  if (Lists.length == LISTS_INIT_SIZE)
  {
    Lists.listsSize += LISTSINCREMENT;
    Lists.elem = (SqList *)realloc(Lists.elem, sizeof(SqList) * Lists.listsSize);
  }
  Lists.elem[Lists.length] = L;
  Lists.length++;
  return OK;
}

status InitLists(LISTS &Lists)
//初始化Lists
{
  if (Lists.elem)
    return INFEASIBLE;
  else
  {
    Lists.length = 0;
    Lists.listsSize = 10;
    Lists.elem = (SqList *)malloc(sizeof(SqList) * LISTS_INIT_SIZE);
    for (int i = 0; i < LISTS_INIT_SIZE; i++)
    {
      Lists.elem[i].elem = NULL;
    }
  }
  return OK;
}

status ListsTraverse(LISTS Lists)
//依次输出Lists中的线性表的元素
{
  if (!Lists.elem)
    return INFEASIBLE;
  if (Lists.length == 0)
  {
    printf("Is Empty!\n");
    return 0;
  }
  for (int i = 0; i < Lists.length; i++)
  {
    ListTraverse(Lists.elem[i]);
  }
  return 1;
}

status LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
  if (!Lists.elem)
    return INFEASIBLE;
  int i;
  for (i = 0; i < Lists.length; i++)
  {
    if (strcmp(Lists.elem[i].name, ListName) == 0)
      return i + 1;
  }
  return 0;
}

status RemoveList(LISTS &Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
  if (!Lists.elem)
    return INFEASIBLE;
  int i;
  for (i = 0; i < Lists.length; i++)
  {
    if (strcmp(Lists.elem[i].name, ListName) == 0)
    {
      DestroyList(Lists.elem[i]);
      Lists.length--;
      for (; i < Lists.length; i++)
      {
        Lists.elem[i] = Lists.elem[i + 1];
      }
      return OK;
    }
  }
  return ERROR;
}
status ReLists(LISTS &Lists)
{
  for (int i = 0; i < Lists.length; i++)
  {
    if (Lists.elem[i].elem == NULL)
    {
      Lists.length--;
      for (int j = i; j < Lists.length; j++)
      {
        Lists.elem[j] = Lists.elem[j + 1];
      }
    }
  }
}

