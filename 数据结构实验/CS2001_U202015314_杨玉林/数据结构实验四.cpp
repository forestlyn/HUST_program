#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType;
typedef enum
{
  DG,
  DN,
  UDG,
  UDN
} GraphKind;
typedef struct
{
  KeyType key;
  char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode
{                          //表结点类型定义
  int adjvex;              //顶点位置编号
  struct ArcNode *nextarc; //下一个表结点指针
} ArcNode;
typedef struct VNode
{                    //头结点及其数组类型定义
  VertexType data;   //顶点信息
  ArcNode *firstarc; //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{                     //邻接表的类型定义
  AdjList vertices;   //头结点数组
  int vexnum, arcnum; //顶点数、弧数
  GraphKind kind;     //图的类型
} ALGraph;
typedef struct
{
  int elem[MAX_VERTEX_NUM];
  int front, tail;
} QUEUE;
typedef struct
{
  ALGraph G;
  char name[30];
} LIST;
typedef struct
{
  LIST elem[20];
  int length;
} LISTS;

int visited[MAX_VERTEX_NUM];
void visit(VertexType v)
{
  printf(" %d %s", v.key, v.others);
}

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status Find(VertexType V[], KeyType VR[][2]);
status CreateVR(VNode &V1, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph &G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KeyType v);
status DeleteVR(ALGraph &G, int adjvex, int result);
status InsertArc(ALGraph &G, KeyType v, KeyType w);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status ALGraphsTraverse(LISTS Lists);
status LocateALGraph(LISTS Lists, char name[]);
status RemoveALGraph(LISTS &Lists, char name[]);
status ALGraphTraverse(ALGraph G);
int main()
{
  LISTS Lists;
  Lists.length = 0;
  char FileName[30] = "ALGraph.txt";
  char Listname[30];
  KeyType u, w;
  int op = 1, now = 0, result, i;
  VertexType value;
  VertexType V[21];
  KeyType VR[100][2];
  for (int i = 0; i < MAX_VERTEX_NUM; i++)
  {
    Lists.elem[i].G.arcnum = 0;
    Lists.elem[i].G.vexnum = 0;
  }
  while (op)
  {
    printf("The op of ALGraphs\n");
    printf("1.AddALGraph\n");
    printf("2.ALGraphsTraverse\n");
    printf("3.LocateALGraph\n");
    printf("4.RemoveALGraph\n");
    printf("5.choose ALGraph\n");
    printf("0.exit\n");
    printf("-------------------------------------------------\n");
    printf("choose [0-5]:");
    scanf("%d", &op);
    while (op)
    {
      switch (op)
      {
      case 1:
        i = 0;
        printf("input the name of ALGraph:");
        scanf("%s", Listname);
        strcpy(Lists.elem[Lists.length].name, Listname);
        printf("input the elem of ALGraph:");
        scanf("%d%s", &V[i].key, V[i].others);
        while (V[i].key != -1)
        {
          i++;
          scanf("%d%s", &V[i].key, V[i].others);
        }
        i = 0;
        scanf("%d%d", &VR[i][0], &VR[i][1]);
        while (VR[i][0] != -1)
        {
          i++;
          scanf("%d%d", &VR[i][0], &VR[i][1]);
        }
        if (CreateCraph(Lists.elem[Lists.length].G, V, VR) != OK)
        {
          printf("ERROR!\n");
          Lists.elem[Lists.length].G.vexnum = 0;
        }
        else
        {
          printf("Success!\n");
          now++;
          Lists.length++;
        }
        break;
      case 2:
        ALGraphsTraverse(Lists);
        break;
      case 3:
        printf("input the name of ALGraph:");
        scanf("%s", Listname);
        result = LocateALGraph(Lists, Listname);
        if (result)
          printf("the ALGraph %s is the %dth ALGraph\n", Listname, result);
        else
          printf("ERROR!\n");
        break;
      case 4:
        printf("input the name of ALGraph:");
        scanf("%s", Listname);
        result = RemoveALGraph(Lists, Listname);
        if (result)
          printf("Success!\n");
        else
          printf("ERROR!\n");
        break;
      case 5:
        printf("input the name of ALGraph:");
        scanf("%s", Listname);
        result = LocateALGraph(Lists, Listname);
        if (result == 0)
        {
          printf("Don't exist!\n");
        }
        else
        {
          system("cls");
          now = result - 1;
          printf("      The ALGraph you choose is %s\n", Lists.elem[now].name);
          printf("      Menu for Linear Table On Sequence Structure \n");
          printf("-------------------------------------------------\n");
          printf("                The op of ALGraph\n");
          printf("    	  1. CreateCraph       2. DestroyGraph\n");
          printf("    	  3. LocateVex         4. PutVex\n");
          printf("    	  5. FirstAdjVex       6. NextAdjVex \n");
          printf("    	  7. InsertVex         8. DeleteVex\n");
          printf("    	  9. InsertArc         10. DeleteArc\n");
          printf("    	  11. DFSTraverse      12. BFSTraverse\n");
          printf("    	  13. SaveGraph        14.LoadGraph\n");
          printf("    	  15. ALGraphTraverse  0.exit   \n");
          printf("-------------------------------------------------\n");
          printf("choose [0-15]:");
          scanf("%d", &op);
          while (op >= 0)
          {

            switch (op)
            {
            case 1:
              //status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
              printf("input the elem of ALGraph:");
              i = 0;
              scanf("%d%s", &V[i].key, V[i].others);
              while (V[i].key != -1)
              {
                i++;
                scanf("%d%s", &V[i].key, V[i].others);
              }
              i = 0;
              scanf("%d%d", &VR[i][0], &VR[i][1]);
              while (VR[i][0] != -1)
              {
                i++;
                scanf("%d%d", &VR[i][0], &VR[i][1]);
              }
              if (CreateCraph(Lists.elem[now].G, V, VR) == OK)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 2:
              //status DestroyGraph(ALGraph &G);
              if (DestroyGraph(Lists.elem[now].G) == OK)
                printf("Success!\n");
              else
                printf("INFEASIBLE!\n");
              getchar();
              break;
            case 3:
              //int LocateVex(ALGraph G, KeyType u);
              printf("please input the key u:\n");
              scanf("%d", &u);
              result = LocateVex(Lists.elem[now].G, u);
              if (result >= 0)
                printf("The Vex %s is the %d vex\n", Lists.elem[now].G.vertices[result].data.others, result);
              else
                printf("ERROR!\n");
              getchar();
              break;
            case 4:
              //status PutVex(ALGraph &G, KeyType u, VertexType value);
              printf("please input the key u, value:\n");
              scanf("%d%d%s", &u, &value.key, value.others);
              result = PutVex(Lists.elem[now].G, u, value);
              if (result == OK)
                printf("Success!\n");
              else
                printf("ERROR!\n");
              getchar();
              break;
            case 5:
              //int FirstAdjVex(ALGraph G, KeyType u);
              printf("please input the key u:\n");
              scanf("%d", &u);
              result = FirstAdjVex(Lists.elem[now].G, u);
              if (result != INFEASIBLE)
                printf("The FirstAdjVex is %d\n", result);
              else
                printf("ERROR!\n");
              getchar();
              break;
            case 6:
              //int NextAdjVex(ALGraph G, KeyType v, KeyType w)
              printf("please input the key u, w:\n");
              scanf("%d%d", &u, &w);
              result = NextAdjVex(Lists.elem[now].G, u, w);
              if (result == INFEASIBLE)
                printf("ERROR!\n");
              else
                printf("The NextAdjVex is %d\n", result);
              getchar();
              break;
            case 7:
              //status InsertVex(ALGraph &G, VertexType v)
              printf("please input the value:\n");
              scanf("%d%s", &value.key, value.others);
              result = InsertVex(Lists.elem[now].G, value);
              if (result == ERROR)
                printf("ERROR!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 8:
              //status DeleteVex(ALGraph &G, KeyType v)
              printf("please input the key u:\n");
              scanf("%d", &u);
              result = DeleteVex(Lists.elem[now].G, u);
              if (result == ERROR)
                printf("ERROR!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 9:
              //status InsertArc(ALGraph &G, KeyType v, KeyType w)
              printf("please input the key u, w:\n");
              scanf("%d%d", &u, &w);
              result = InsertArc(Lists.elem[now].G, u, w);
              if (result == ERROR)
                printf("ERROR!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 10:
              //status DeleteArc(ALGraph &G, KeyType v, KeyType w)
              printf("please input the key u, w:\n");
              scanf("%d%d", &u, &w);
              result = DeleteArc(Lists.elem[now].G, u, w);
              if (result == ERROR)
                printf("ERROR!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 11:
              //status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
              result = DFSTraverse(Lists.elem[now].G, visit);
              if (result == OK)
                printf("\n");
              getchar();
              break;
            case 12:
              //status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
              result = BFSTraverse(Lists.elem[now].G, visit);
              if (result == OK)
                printf("\n");
              getchar();
              break;
            case 13:
              //status SaveGraph(ALGraph G, char FileName[])
              result = SaveGraph(Lists.elem[now].G, FileName);
              if (result == ERROR)
                printf("ERROR!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 14:
              //status LoadGraph(ALGraph &G, char FileName[])
              result = LoadGraph(Lists.elem[now].G, FileName);
              if (result == ERROR)
                printf("ERROR!\n");
              else
                printf("Success!\n");
              getchar();
              break;
            case 15:
              //status ALGraphTraverse(ALGraph G)
              ALGraphTraverse(Lists.elem[now].G);
              getchar();
              break;
            default:
              break;
            }
            if (op == 0)
            {
              system("cls");
              printf("The op of ALGraphs\n");
              printf("1.AddALGraph\n");
              printf("2.ALGraphsTraverse\n");
              printf("3.LocateALGraph\n");
              printf("4.RemoveALGraph\n");
              printf("5.choose ALGraph\n");
              printf("0.exit\n");
              printf("-------------------------------------------------\n");
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

status Find(VertexType V[], KeyType VR[][2])
{
  int i, j;
  KeyType a[100];
  for (i = 0; V[i].key != -1; i++)
  {
    a[i] = V[i].key;
    for (j = i + 1; V[j].key != -1; j++)
    {
      if (V[i].key == V[j].key)
        return ERROR;
    }
  }
  a[i] = -1;
  int flag;
  for (i = 0; VR[i][0] != -1; i++)
  {
    flag = 0;
    for (j = 0; a[j] != -1; j++)
    {
      if (VR[i][0] == a[j])
        flag++;
      if (VR[i][1] == a[j])
        flag++;
    }
    if (flag != 2)
      return ERROR;
  }
  return OK;
}
status CreateVR(VNode &V1, VertexType V[], KeyType VR[][2])
{
  int i, j, k;
  ArcNode *head, *q;
  for (i = 0; VR[i][0] != -1; i++)
  {
    if (VR[i][0] == V1.data.key || VR[i][1] == V1.data.key)
    {
      k = VR[i][0] == V1.data.key ? 1 : 0;
      for (j = 0; V[j].key != -1; j++)
      {
        if (V[j].key == VR[i][k])
          break;
      }
      head = V1.firstarc;
      q = (ArcNode *)malloc(sizeof(ArcNode));
      q->adjvex = j;
      q->nextarc = head;
      V1.firstarc = q;
    }
  }
  return OK;
}
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
  if (!Find(V, VR))
    return ERROR;
  if (G.vexnum > 0)
  {
    printf("G.vexnum:%d\n", G.vexnum);
    return ERROR;
  }

  else
  {
    int i, j;
    for (i = 0; V[i].key != -1; i++)
    {
      G.vertices[i].data = V[i];
      G.vertices[i].firstarc = NULL;
      CreateVR(G.vertices[i], V, VR);
    }

    if (i > MAX_VERTEX_NUM || i < 1)
    {
      //printf("%d\n", i);
      return ERROR;
    }
    //printf("%d\n", i);
    G.vexnum = i;
    //printf("%d\n", G.vexnum);
    for (j = 0; VR[j][0] != -1;)
      j++;
    G.arcnum = j;
  }
  return OK;
}
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
  if (G.vexnum < 1)
    return ERROR;
  ArcNode *p, *q;
  for (int i = 0; i < G.vexnum; i++)
  {
    p = G.vertices[i].firstarc;
    while (p)
    {
      q = p->nextarc;
      free(p);
      p = q;
    }
  }
  G.vexnum = G.arcnum = 0;
  return OK;
}
int LocateVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
  for (int i = 0; i < G.vexnum; i++)
  {
    if (G.vertices[i].data.key == u)
      return i;
  }
  return -1;
}
status FindKey(ALGraph G, KeyType u, VertexType value)
//判断value中的key值和其它key值有无冲突
{
  if (u == value.key)
    return OK;
  else
  {
    for (int i = 0; i < G.vexnum; i++)
    {
      if (G.vertices[i].data.key == value.key)
        return -1;
    }
  }
  return OK;
}
status PutVex(ALGraph &G, KeyType u, VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
  int i = LocateVex(G, u);
  if (i == -1)
    return ERROR;
  if (FindKey(G, u, value) == -1)
    return ERROR;
  G.vertices[i].data = value;
  return OK;
}
int FirstAdjVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
  int result = LocateVex(G, u);
  if (result == -1)
    return -1;
  else if (G.vertices[result].firstarc)
    return G.vertices[result].firstarc->adjvex;
  return -1;
}
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
  int result1, result2;
  result1 = LocateVex(G, v);
  result2 = LocateVex(G, w);
  if (result1 == -1 || result2 == -1)
    return -1;
  else
  {
    ArcNode *p = G.vertices[result1].firstarc;
    while (p)
    {
      if (p->adjvex == result2)
      {
        p = p->nextarc;
        if (p)
          return p->adjvex;
        else
          return -1;
      }
      p = p->nextarc;
    }
  }
  return -1;
}
status InsertVex(ALGraph &G, VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
  if (LocateVex(G, v.key) != -1 || G.vexnum >= 20)
    return ERROR;
  else
  {
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
  }
}
status DeleteVR(ALGraph &G, int adjvex, int result)
//adjvex是待删除的结点序号，result是待操作的结点序号
{
  ArcNode *p1, *p2;
  p1 = G.vertices[result].firstarc;
  if (p1)
    p2 = p1->nextarc;
  else
    return OK;
  if (p1->adjvex == adjvex)
  {
    free(p1);
    p1 = NULL;
    G.vertices[result].firstarc = p2;
    G.arcnum--;
  }
  else
  {
    while (p2)
    {
      if (p2->adjvex == adjvex)
      {
        G.arcnum--;
        p1->nextarc = p2->nextarc;
        free(p2);
        p2 = NULL;
        return OK;
      }
      else
      {
        p1 = p2;
        p2 = p1->nextarc;
      }
    }
  }
  return OK;
}
status DeleteV(ALGraph &G, int adjvex)
{
  ArcNode *p1;
  for (int i = 0; i < G.vexnum; i++)
  {
    DeleteVR(G, adjvex, i);
    p1 = G.vertices[i].firstarc;
    while (p1)
    {
      if (p1->adjvex > adjvex)
        p1->adjvex = p1->adjvex - 1;
      p1 = p1->nextarc;
    }
  }
  return OK;
}
status DeleteVex(ALGraph &G, KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
  if (G.vexnum < 1)
    return ERROR;
  int result = LocateVex(G, v);
  if (result == -1)
    return ERROR;
  else
  {
    G.vexnum--;
    ArcNode *p1, *p2;
    p1 = G.vertices[result].firstarc;
    while (p1)
    {
      p2 = p1->nextarc;
      free(p1);
      p1 = NULL;
      p1 = p2;
    }
    for (int i = result; i < G.vexnum; i++)
    {
      G.vertices[i] = G.vertices[i + 1];
    }
    DeleteV(G, result);
    return OK;
  }
}
status InsertArc(ALGraph &G, KeyType v, KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
  int result1 = LocateVex(G, v);
  int result2 = LocateVex(G, w);
  if (result1 == -1 || result2 == -1)
    return ERROR;
  else
  {
    ArcNode *p = G.vertices[result1].firstarc;
    while (p)
    {
      if (p->adjvex == result2)
        return ERROR;
      p = p->nextarc;
    }
    ArcNode *p1, *p2;
    p1 = (ArcNode *)malloc(sizeof(ArcNode));
    p1->adjvex = result2;
    p1->nextarc = G.vertices[result1].firstarc;
    G.vertices[result1].firstarc = p1;
    p2 = (ArcNode *)malloc(sizeof(ArcNode));
    p2->adjvex = result1;
    p2->nextarc = G.vertices[result2].firstarc;
    G.vertices[result2].firstarc = p2;
    G.arcnum++;
    return OK;
  }
}
status DeleteArc(ALGraph &G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
  int result1 = LocateVex(G, v);
  int result2 = LocateVex(G, w);
  if (result1 == -1 || result2 == -1)
    return ERROR;
  else
  {
    ArcNode *p = G.vertices[result1].firstarc;
    int flag = 0;
    while (p)
    {
      if (p->adjvex == result2)
      {
        flag = 1;
        break;
      }
      p = p->nextarc;
    }
    if (flag == 0)
      return ERROR;
    else
    {
      DeleteVR(G, result1, result2);
      DeleteVR(G, result2, result1);
      G.arcnum++;
    }
    return OK;
  }
}

void DFS(ALGraph &G, int i, void (*visit)(VertexType))
{
  visited[i] = TRUE;
  visit(G.vertices[i].data);
  ArcNode *p;
  p = G.vertices[i].firstarc;
  while (p)
  {
    if (!visited[p->adjvex])
    {
      DFS(G, p->adjvex, visit);
    }
    p = p->nextarc;
  }
}
status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
  int i;
  for (int j = 0; j < G.vexnum; j++)
  {
    visited[j] = FALSE;
  }
  for (i = 0; i < G.vexnum; i++)
  {
    if (!visited[i])
    {
      DFS(G, i, visit);
    }
  }
  return OK;
}

status InitQueue(QUEUE &Q)
{
  Q.front = Q.tail = 0;
  return OK;
}
status QueueEmpty(QUEUE Q)
{
  if (Q.front == Q.tail)
    return OK;
  return ERROR;
}
status QueueFull(QUEUE Q)
{
  if ((Q.tail + MAX_VERTEX_NUM - Q.front) % MAX_VERTEX_NUM == MAX_VERTEX_NUM - 1)
    return OK;
  return ERROR;
}
status EnQueue(QUEUE &Q, int v)
{
  if (QueueFull(Q))
    return ERROR;
  Q.elem[Q.tail] = v;
  Q.tail = (Q.tail + 1) % MAX_VERTEX_NUM;
  return OK;
}
status DeQueue(QUEUE &Q, int &v)
{
  if (QueueEmpty(Q))
    return ERROR;
  v = Q.elem[Q.front];
  Q.front = (Q.front + 1) % MAX_VERTEX_NUM;
  return OK;
}
status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
  QUEUE Q;
  InitQueue(Q);
  for (int i = 0; i < G.vexnum; i++)
  {
    visited[i] = FALSE;
  }
  for (int i = 0; i < G.vexnum; i++)
  {
    if (!visited[i])
    {
      visited[i] = TRUE;
      visit(G.vertices[i].data);
      EnQueue(Q, i);
      while (!QueueEmpty(Q))
      {
        DeQueue(Q, i);
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
          if (!visited[p->adjvex])
          {
            visited[p->adjvex] = TRUE;
            visit(G.vertices[p->adjvex].data);
            EnQueue(Q, p->adjvex);
          }
          p = p->nextarc;
        }
      }
    }
  }
  return OK;
}
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
  if (G.vexnum < 1)
    return ERROR;
  FILE *fp = fopen(FileName, "w");
  ArcNode *p;
  putc(G.vexnum, fp);
  putc(G.arcnum, fp);
  for (int i = 0; i < G.vexnum; i++)
  {
    fwrite(&G.vertices[i].data, sizeof(VNode), 1, fp);
  }
  for (int i = 0; i < G.vexnum; i++)
  {
    p = G.vertices[i].firstarc;
    while (p)
    {
      putc(p->adjvex, fp);
      p = p->nextarc;
    }
    putc(21, fp);
  }
  fclose(fp);
  return OK;
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
  if (G.vexnum > 0)
    return ERROR;
  FILE *fp = fopen(FileName, "r");
  ArcNode *p;
  G.vexnum = getc(fp);
  G.arcnum = getc(fp);
  for (int i = 0; i < G.vexnum; i++)
  {
    fread(&G.vertices[i].data, sizeof(VNode), 1, fp);
    G.vertices[i].firstarc = NULL;
  }
  int j;
  int adj[20];
  for (int i = 0; i < G.vexnum; i++)
  {
    for (j = 0; (adj[j] = getc(fp)) >= 0; j++)
    {
      if (adj[j] == 21)
        break;
    }
    j--;
    while (j >= 0)
    {
      p = (ArcNode *)malloc(sizeof(ArcNode));
      p->adjvex = adj[j--];
      p->nextarc = G.vertices[i].firstarc;
      G.vertices[i].firstarc = p;
    }
  }
  fclose(fp);
  return OK;
}
status ALGraphTraverse(ALGraph G)
{
  for (int i = 0; i < G.vexnum; i++)
  {
    visit(G.vertices[i].data);
    ArcNode *p = G.vertices[i].firstarc;
    while (p)
    {
      printf(" %d", p->adjvex);
      p = p->nextarc;
    }
    printf("\n");
  }
  return OK;
}
status ALGraphsTraverse(LISTS Lists)
{
  for (int i = 0; i < Lists.length; i++)
  {
    printf("%s ", Lists.elem[i].name);
    BFSTraverse(Lists.elem[i].G, visit);
    printf("\n");
  }
  return OK;
}
status LocateALGraph(LISTS Lists, char name[])
{
  for (int i = 0; i < Lists.length; i++)
  {
    if (strcmp(Lists.elem[i].name, name) == 0)
    {
      return i + 1;
    }
  }
  return ERROR;
}
status RemoveALGraph(LISTS &Lists, char name[])
{
  int result = LocateALGraph(Lists, name);
  if (!result)
  {
    return ERROR;
  }
  else
  {
    Lists.length--;
    for (int i = result - 1; i < Lists.length; i++)
    {
      Lists.elem[i] = Lists.elem[i + 1];
    }
    DestroyGraph(Lists.elem[Lists.length].G);
  }
  return OK;
}

