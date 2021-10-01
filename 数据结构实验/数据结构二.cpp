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

typedef int ElemType;
typedef struct LNode
{ //单链表（链式结构）结点的定义
  ElemType data;
  struct LNode *next;
} LNode, *LinkList;
typedef struct List
{
  LinkList L;
  char name[30];
} List;
typedef struct Lists
{
  List *elem;
  ElemType length;
  ElemType listsSize;
} LISTS;

status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType &e);
status LocateElem(LinkList L, ElemType e);
status PriorElem(LinkList L, ElemType e, ElemType &pre);
status NextElem(LinkList L, ElemType e, ElemType &next);
status ListInsert(LinkList &L, int i, ElemType e);
status ListDelete(LinkList &L, int i, ElemType &e);
status ListTraverse(LinkList L);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);
status AddList(LISTS &Lists, LinkList L);
status ListsTraverse(LISTS Lists);
status LocateList(LISTS Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
status reLists(LISTS &Lists);
int main()
{
  LISTS Lists;
  Lists.length = 0;
  Lists.listsSize = 10;
  Lists.elem = (List *)malloc(sizeof(List) * LISTS_INIT_SIZE);
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
          Lists.elem = (List *)realloc(Lists.elem, sizeof(List) * Lists.listsSize);
        }
        printf("input the name of list:");
        scanf("%s", Listname);
        strcpy(Lists.elem[Lists.length].name, Listname);
        printf("input the elem of list:");
        Lists.elem[Lists.length].L = NULL;
        if (InitList(Lists.elem[Lists.length].L) != 1)
          printf("ERROR!");
        int temp;
        scanf("%d", &temp);
        while (temp)
        {
          ListInsert(Lists.elem[Lists.length].L, ListLength(Lists.elem[Lists.length].L) + 1, temp);
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
              if (InitList(Lists.elem[now].L) == OK)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 2:
              //status DestroyList(LinkList &L)
              if (DestroyList(Lists.elem[now].L) == OK && Lists.elem[now].L == NULL)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 3:
              //status ClearList(LinkList &L)
              if (ClearList(Lists.elem[now].L) == OK)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 4:
              //status ListEmpty(LinkList L)
              result = ListEmpty(Lists.elem[now].L);
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
              result = ListLength(Lists.elem[now].L);
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
              result = GetElem(Lists.elem[now].L, i, e);
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
              result = LocateElem(Lists.elem[now].L, e);
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
              result = PriorElem(Lists.elem[now].L, e, pre);
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
              result = NextElem(Lists.elem[now].L, e, next);
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
              result = ListInsert(Lists.elem[now].L, i, e);
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
              result = ListDelete(Lists.elem[now].L, i, e);
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
              result = ListTraverse(Lists.elem[now].L);
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
              result = SaveList(Lists.elem[now].L, filename1);
              if (result == INFEASIBLE)
                printf("INFEASIBLE!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 14:
              //status LoadList(LinkList &L, char FileName[])
              result = LoadList(Lists.elem[now].L, filename1);
              if (result == INFEASIBLE)
                printf("INFEASIBLE!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            default:
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
              reLists(Lists);
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

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
  if (L)
    return INFEASIBLE;
  else
  {
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
  }
  return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    free(L);
    L = NULL;
  }
  return OK;
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    LinkList p = L;
    LinkList p1 = p->next;
    while (p1 != NULL)
    {
      p = p1;
      p1 = p->next;
      free(p);
    }
    L->next = NULL;
  }
  return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    if (L->next == NULL)
      return TRUE;
    else
      return FALSE;
  }
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
      i++;
      p = p->next;
    }
    return i;
  }
}

status GetElem(LinkList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else if (i < 1)
    return ERROR;
  else
  {
    int j = 1;
    LinkList p = L->next;
    while (p)
    {
      if (i == j)
      {
        e = p->data;
        return OK;
      }
      p = p->next;
      j++;
    }
  }
  return ERROR;
}

status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    int i = 1;
    LinkList p = L->next;
    while (p)
    {
      if (p->data == e)
      {
        return i;
      }
      p = p->next;
      i++;
    }
  }
  return ERROR;
}

status PriorElem(LinkList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    LinkList p = L;
    LinkList p1 = p->next;
    while (p1 && p1->next)
    {
      p = p1;
      p1 = p->next;
      if (p1->data == e)
      {
        pre = p->data;
        return OK;
      }
    }
  }
  return ERROR;
}

status NextElem(LinkList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    LinkList p = L;
    LinkList p1 = p->next;
    while (p1 && p1->next)
    {
      p = p1;
      p1 = p1->next;
      if (p->data == e)
      {
        next = p1->data;
        return OK;
      }
    }
  }
  return ERROR;
}

status ListInsert(LinkList &L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else if (i < 1)
    return ERROR;
  else
  {
    int j = 1;
    LinkList p = L;
    LinkList p1 = p->next;
    while (p)
    {
      if (j == i)
      //找到当前插入位置
      {
        LinkList p2;
        p2 = (LinkList)malloc(sizeof(LNode));
        p2->data = e;
        p->next = p2;
        p2->next = p1;
        return OK;
      }
      if (!p1)
      //已经到结尾还未找到插入位置
      {
        return ERROR;
      }
      p = p1;
      p1 = p->next;
      j++;
    }
  }
  return ERROR;
}

status ListDelete(LinkList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  if (i < 1)
    return ERROR;
  else
  {
    int j = 1;
    LinkList p = L;
    LinkList p1 = p->next;
    while (p1)
    {
      if (j == i)
      {
        e = p1->data;
        p->next = p1->next;
        free(p1);
        return OK;
      }
      p = p1;
      p1 = p->next;
      j++;
    }
  }
  return ERROR;
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    L = L->next;
    while (L)
    {
      printf("%d ", L->data);
      L = L->next;
    }
    printf("\n");
  }
  return OK;
}

status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
  if (!L)
    return INFEASIBLE;
  else
  {
    FILE *fp = fopen(FileName, "w");
    L = L->next;
    while (L)
    {
      putc(L->data, fp);
      L = L->next;
    }
    fclose(fp);
  }
  return OK;
}

status LoadList(LinkList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
  if (L)
    return INFEASIBLE;
  else
  {
    FILE *fp = fopen(FileName, "r");
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList p = L, p1;
    ElemType t;
    while ((t = getc(fp)) != EOF)
    {
      p1 = (LinkList)malloc(sizeof(LNode));
      p1->data = t;
      p->next = p1;
      p = p1;
    }
    p->next = NULL;
    fclose(fp);
  }
  return OK;
}
status AddList(LISTS &Lists, LinkList L)
// 将当前线性表L加入到Lists中
{
  if (!L)
    return INFEASIBLE;
  if (!Lists.elem)
    return INFEASIBLE;
  if (Lists.length == LISTS_INIT_SIZE)
  {
    Lists.listsSize += LISTSINCREMENT;
    Lists.elem = (List *)realloc(Lists.elem, sizeof(List) * Lists.listsSize);
  }
  printf("please input the name of List: ");
  scanf("%s", Lists.elem[Lists.length].name);
  Lists.elem[Lists.length].L = L;
  Lists.length++;
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
    printf("%s  ", Lists.elem[i].name);
    ListTraverse(Lists.elem[i].L);
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
      DestroyList(Lists.elem[i].L);
      Lists.elem[i].name[0] = '/0';
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
status reLists(LISTS &Lists)
{
  for (int i = 0; i < Lists.length; i++)
  {
    if (Lists.elem[i].L == NULL)
    {
      Lists.length--;
      for (int j = i; j < Lists.length; j++)
      {
        Lists.elem[j].L = Lists.elem[j + 1].L;
        strcpy(Lists.elem[j].name, Lists.elem[j + 1].name);
      }
    }
  }
}

