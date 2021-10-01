#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct
{
  KeyType key;
  char others[100];
} TElemType; //二叉树结点类型定义

typedef struct BiTNode
{ //二叉链表结点的定义
  TElemType data;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct
{
  BiTree T;
  char name[30];
} List;

void visit(BiTree T)
{
  printf(" %d,%s ", T->data.key, T->data.others);
}

status CreateBiTree(BiTree &T, TElemType definition[]);
status FindKey(TElemType definition[]);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
BiTree CreateTree(TElemType definition[]);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode *LocateNode(BiTree T, KeyType e);
BiTNode *LocateFatherNode(BiTree T, KeyType e);
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode *GetSibling(BiTree T, KeyType e);
status find(BiTree T, KeyType key);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
int main()
{
  char filename[30] = "BiTree.txt";
  int e, result;
  int op = 1;
  TElemType defination[100];
  TElemType value;
  BiTree p, T = NULL;
  int LR;
  int def_i;
  while (op)
  {
    system("cls");
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("                The op of List\n");
    printf("    	  1. CreateBiTree       2. DestroyBiTree\n");
    printf("    	  3. ClearBiTree      4. BiTreeEmpty\n");
    printf("    	  5. BiTreeDepth     6. LocateNode \n");
    printf("    	  7. Assign     8. GetSibling\n");
    printf("    	  9. InsertNode       10. DeleteNode\n");
    printf("    	  11. PreOrderTraverse    12. InOrderTraverse\n");
    printf("    	  13. PostOrderTraverse      14.LevelOrderTraverse\n");
    printf("    	  15.SaveBiTree     16.LoadBiTree   \n");
    printf("    	  0.exit   \n");
    printf("-------------------------------------------------\n");
    printf("choose [0-16]:");
    scanf("%d", &op);
    while (op >= 0)
    {
      switch (op)
      {
      case 1:
        //status CreateBiTree(BiTree &T, TElemType definition[]);
        printf("input the elem of list:");
        def_i = 0;
        scanf("%d%s", &defination[def_i].key, defination[def_i].others);
        while (defination[def_i].key != -1)
        {
          def_i++;
          scanf("%d%s", &defination[def_i].key, defination[def_i].others);
        }
        if (CreateBiTree(T, defination) == OK)
          printf("Success!\n");
        else
          printf("INFEASIBLE!\n");

        getchar();
        break;
      case 2:
        //status DestroyBiTree(BiTree &T)
        if (T != NULL && DestroyBiTree(T) == OK)
          printf("Success!\n");
        else
          printf("INFEASIBLE!\n");
        getchar();
        break;
      case 3:
        //status ClearBiTree(BiTree &T)
        if (ClearBiTree(T) == OK)
          printf("Success!\n");
        else
          printf("INFEASIBLE!\n");
        getchar();
        break;
      case 4:
        //status BiTreeEmpty(BiTree T)
        result = BiTreeEmpty(T);
        if (result == TRUE)
          printf("is Empty!\n");
        else if (result == FALSE)
          printf("isn't Empty!\n");
        else
          printf("INFEASIBLE!\n");
        getchar();
        break;
      case 5:
        //int BiTreeDepth(BiTree T)
        result = BiTreeDepth(T);
        printf("The depth is %d\n", result);
        getchar();
        break;
      case 6:
        //BiTNode *LocateNode(BiTree T, KeyType e)
        printf("please input the key e:\n");
        scanf("%d", &e);
        p = LocateNode(T, e);
        if (p == NULL)
          printf("ERROR!\n");
        else
        {
          printf("Success!\np:");
          visit(p);
          printf("\n");
        }
        getchar();
        break;
      case 7:
        //status Assign(BiTree &T, KeyType e, TElemType value)
        printf("please input the key e and value.key, value.others:\n");
        scanf("%d%d%s", &e, &value.key, value.others);
        result = Assign(T, e, value);
        if (result == NULL)
          printf("ERROR!\n");
        else
          printf("Success!\n");
        getchar();
        break;
      case 8:
        //BiTNode *GetSibling(BiTree T, KeyType e)
        printf("please input the key e:\n");
        scanf("%d", &e);
        p = GetSibling(T, e);
        if (p == NULL)
          printf("ERROR!\n");
        else
        {
          printf("Success!\np:");
          visit(p);
          printf("\n");
        }
        getchar();
        break;
      case 9:
        //status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
        printf("please input the key e, LR, value.key, value.others:\n");
        scanf("%d%d%d%s", &e, &LR, &value.key, value.others);
        result = InsertNode(T, e, LR, value);
        if (result == ERROR)
          printf("ERROR!\n");
        else if (result == OK)
          printf("Success!\n");
        getchar();
        break;
      case 10:
        //status DeleteNode(BiTree &T, KeyType e)
        printf("please input the number e:\n");
        scanf("%d", &e);
        result = DeleteNode(T, e);
        if (result == ERROR)
          printf("ERROR!\n");
        else if (result == OK)
          printf("Success!\n");
        getchar();
        break;
      case 11:
        //status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
        result = PreOrderTraverse(T, visit);
        printf("\n");
        getchar();
        break;
      case 12:
        //status InOrderTraverse(BiTree T, void (*visit)(BiTree))
        result = InOrderTraverse(T, visit);
        printf("\n");
        getchar();
        break;
      case 13:
        //status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
        result = PostOrderTraverse(T, visit);
        printf("\n");
        getchar();
        break;
      case 14:
        //status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
        result = LevelOrderTraverse(T, visit);
        printf("\n");
        getchar();
        break;
      case 15:
        //status SaveBiTree(BiTree T, char FileName[])
        result = SaveBiTree(T, filename);
        if (result == ERROR)
          printf("ERROR!\n");
        else
          printf("Success!\n");
        getchar();
        break;
      case 16:
        //status LoadBiTree(BiTree &T, char FileName[])
        result = LoadBiTree(T, filename);
        if (result == ERROR)
          printf("ERROR!\n");
        else
          printf("Success!\n");
        getchar();
        break;
      default:
        break;
      }
      if (op == 0)
        break;
      printf("choose [0-16]:");
      scanf("%d", &op);
    }
  }
  return 0;
}

int def_Create_i = 0;
status CreateBiTree(BiTree &T, TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
  if (!FindKey(definition))
    return ERROR;
  else
  {
    T = CreateTree(definition);
    def_Create_i = 0;
  }
  return OK;
}
BiTree CreateTree(TElemType definition[])
{
  BiTree T;
  if (definition[def_Create_i].key == 0)
  {
    def_Create_i++;
    T = NULL;
  }
  else
  {
    T = new BiTNode;
    T->data = definition[def_Create_i];
    def_Create_i++;
    T->lchild = CreateTree(definition);
    T->rchild = CreateTree(definition);
  }
  return T;
}
status FindKey(TElemType definition[])
{
  for (int i = 0; definition[i].key != -1; i++)
  {
    for (int j = i + 1; definition[j].key != -1; j++)
    {
      if (definition[i].key == definition[j].key && definition[i].key != 0)
        return ERROR;
    }
  }
  return OK;
}

status DestroyBiTree(BiTree &T)
{
  if (!T)
    return OK;
  else
  {
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
  }
}
status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
  if (!T)
    return OK;
  ClearBiTree(T->lchild);
  ClearBiTree(T->rchild);
  free(T);
  T = NULL;
  return OK;
}
status BiTreeEmpty(BiTree T)
{
  if (!T)
    return TRUE;
  else
    return FALSE;
}
int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
  if (!T)
    return 0;
  else
  {
    int l = BiTreeDepth(T->lchild);
    int r = BiTreeDepth(T->rchild);
    return l > r ? l + 1 : r + 1;
  }
}

BiTNode *LocateNode(BiTree T, KeyType e)
//查找结点
{
  BiTree p;
  if (!T)
    return NULL;
  else
  {
    if (T->data.key == e)
    {
      return T;
    }
    else
      p = LocateNode(T->lchild, e);
    if (p)
      return p;
    else
      return LocateNode(T->rchild, e);
  }
}

status Assign(BiTree &T, KeyType e, TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
  if (!find(T, value.key) && e != value.key)
    return NULL;
  BiTree p = LocateNode(T, e);
  if (!p)
    return NULL;
  else
  {
    p->data = value;
    return OK;
  }
}
BiTNode *GetSibling(BiTree T, KeyType e)
//实现获得兄弟结点
{
  BiTree p;
  if (!T)
    return NULL;
  else
  {
    if (T->lchild && T->lchild->data.key == e)
      return T->rchild;
    else if (T->rchild && T->rchild->data.key == e)
      return T->lchild;
    else
      p = GetSibling(T->lchild, e);
    if (p)
      return p;
    else
      return GetSibling(T->rchild, e);
  }
}
status find(BiTree T, KeyType key)
//查找key为e的结点，存在返回ERROR,不存在返回OK
{
  int i;
  if (!T)
    return OK;
  else
  {
    if (T->data.key == key)
    {
      return ERROR;
    }
    else
      i = find(T->lchild, key);
    if (i == 0)
      return ERROR;
    else
      return find(T->rchild, key);
  }
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
  if ((find(T, c.key) == ERROR))
  {
    //printf("ERROR 1");
    return ERROR;
  }
  if ((find(T, e) == OK))
  {
    //printf("ERROR 2");
    return ERROR;
  }
  else
  {
    BiTree p = LocateNode(T, e);
    if (!p)
    {
      //printf("ERROR 3");
      return ERROR;
    }
    BiTree q;
    BiTree m = (BiTNode *)malloc(sizeof(BiTNode));
    m->data = c;
    m->lchild = NULL;
    m->rchild = NULL;
    if (LR == -1)
    {
      q = T;
      m->rchild = T;
      T = m;
    }
    else if (LR == 0)
    {
      q = p->lchild;
      p->lchild = m;
      m->rchild = q;
    }
    else if (LR == 1)
    {
      q = p->rchild;
      p->rchild = m;
      m->rchild = q;
    }
    return OK;
  }
}
BiTNode *LocateFatherNode(BiTree T, KeyType e)
//查找父亲结点
{
  BiTree p;
  if (!T)
    return NULL;
  if ((!T->lchild) && (!T->rchild))
    return NULL;
  else
  {
    if (T->lchild && T->lchild->data.key == e)
    {
      return T;
    }
    else if (T->rchild && T->rchild->data.key == e)
      return T;
    else
      p = LocateFatherNode(T->lchild, e);
    if (p)
      return p;
    else
      return LocateFatherNode(T->rchild, e);
  }
}
status DeleteNode(BiTree &T, KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
	if(!T)
	  return ERROR; 
  if (T->data.key == e)
  {
    if (T->lchild && T->rchild)
    {
      BiTree l = T->lchild;
      BiTree r = T->rchild;
      free(T);
      T = l;
      while (l->rchild)
        l = l->rchild;
      l->rchild = r;
    }
    else if ((!T->lchild) && (!T->rchild))
    {
      free(T);
      T = NULL;
    }
    else if ((T->lchild && (!T->rchild)))
    {
      BiTree q = T->lchild;
      free(T);
      T = q;
    }
    else if ((!T->lchild) && T->rchild)
    {
      BiTree q = T->rchild;
      free(T);
      T = q;
    }
    return OK;
  }
  BiTree p = LocateFatherNode(T, e);
  if (!p)
    return ERROR;
  BiTree q = p->lchild && p->lchild->data.key == e ? p->lchild : p->rchild;
  int i = p->lchild && p->lchild->data.key == e ? 0 : 1;
  if (p && q)
  {
    if (q->lchild && q->rchild)
    {
      BiTree l = q->lchild;
      BiTree r = q->rchild;
      free(q);
      q = l;
      while (l->rchild)
        l = l->rchild;
      l->rchild = r;
      if (i)
        p->lchild = q;
      else
        p->lchild = q;
    }
    else if ((!q->lchild) && (!q->rchild))
    {
      free(q);
      q = NULL;
      if (i)
        p->lchild = NULL;
      else
        p->lchild = NULL;
    }
    else if ((q->lchild && (!q->rchild)))
    {
      BiTree m = q->lchild;
      free(q);
      q = m;
      if (i)
        p->lchild = q;
      else
        p->lchild = q;
    }
    else if ((!q->lchild) && q->rchild)
    {
      BiTree m = q->rchild;
      free(q);
      q = m;
      if (i)
        p->lchild = q;
      else
        p->lchild = q;
    }
    return OK;
  }
}

typedef struct
{
  BiTree *elem;
  int top;
  int base;
} SqStack;
#define MAXSIZE 100
int initStack(SqStack &S)
{
  S.elem = (BiTree *)malloc(sizeof(BiTree) * 100);
  S.top = S.base = 0;
  return 1;
}
int pop(SqStack &S, BiTree &q)
{
  if (S.top == S.base)
    return 0;
  else
  {
    q = S.elem[--S.top];
    return 1;
  }
}
int push(SqStack &S, BiTree &q)
{
  if (S.top - S.base == MAXSIZE)
    return 0;
  else
  {
    S.elem[S.top++] = q;
    return 1;
  }
}
int StackEmpty(SqStack S)
{
  if (S.top == S.base)
    return 1;
  return 0;
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
  SqStack S;
  initStack(S);
  BiTree q;
  if (T)
    push(S, T);
  while (!StackEmpty(S))
  {
    q = NULL;
    pop(S, q);
    if (q)
      visit(q);
    if (q && q->rchild)
      push(S, q->rchild);
    if (q && q->lchild)
      push(S, q->lchild);
  }
  return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
  SqStack S;
  initStack(S);
  BiTree q = T;
  while (!StackEmpty(S) || q)
  {
    if (q)
    {
      push(S, q);
      q = q->lchild;
    }
    else
    {
      pop(S, q);
      visit(q);
      q = q->rchild;
    }
  }
  return OK;
}

/*status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//先序遍历二叉树T
{
  if (T)
  {
    visit(T);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
  }
  return OK;
}
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//中序遍历二叉树T
{
  if (T)
  {
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
  }
  return OK;
}*/
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//后序遍历二叉树T
{
  if (T)
  {
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
  }
  return OK;
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//按层遍历二叉树T
{
  int length = 0;
  BiTree List[100];
  BiTree p = NULL;
  if (T)
  {
    List[length++] = T;
  }
  while (length > 0)
  {
    p = List[0];
    for (int j = 0; j + 1 < length; j++)
    {
      List[j] = List[j + 1];
    }
    length--;
    visit(p);
    if (p->lchild) //左孩子不空，入队列
    {
      List[length++] = p->lchild;
    }
    if (p->rchild) //右孩子不空，入队列
    {
      List[length++] = p->rchild;
    }
  }
  return OK;
}

status write(BiTree T, FILE *fp)
{
  if (!T)
  {
    BiTree p = (BiTree)malloc(sizeof(BiTNode));
    p->data.key = 0;
    strcpy(p->data.others, "NULL");
    fwrite(p, sizeof(BiTree), 1, fp);
    return NULL;
  }
  else
  {
    fwrite(T, sizeof(BiTree), 1, fp);
    write(T->lchild, fp);
    write(T->rchild, fp);
    return OK;
  }
}
status read(BiTree &T, FILE *fp)
{
  if (feof(fp))
    return OK;
  BiTree p = (BiTree)malloc(sizeof(BiTNode));
  fread(p, sizeof(BiTree), 1, fp);
  if (p->data.key)
  {
    T = p;
    T->lchild = T->rchild = NULL;
    read(T->lchild, fp);
    read(T->rchild, fp);
  }
  else
  {
    T = NULL;
  }
  return OK;
}
status SaveBiTree(BiTree T, char FileName[])
{
  if (!T)
    return ERROR;
  else
  {
    FILE *fp = fopen(FileName, "w");
    write(T, fp);
    fclose(fp);
    return OK;
  }
}
status LoadBiTree(BiTree &T, char FileName[])
{
  if (T)
    return ERROR;
  else
  {
    FILE *fp = fopen(FileName, "r");
    read(T, fp);
    fclose(fp);
    return OK;
  }
}

