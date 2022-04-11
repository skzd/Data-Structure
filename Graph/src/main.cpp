//
// Created by 孙克政 on 2022/4/11.
//

#include <stdio.h>
#include <cstdlib>
#include <cstring>

#define MAX 100
#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

typedef struct ENode{   // 邻接表中表对应的链表的顶点
    int ivex; // 边所指向顶点的位置
    struct ENode *next_edge; // 指向下一条弧的指针
}ENode, *PENode;

typedef struct VNode{ // 邻接表中表的顶点
    char data; //顶点信息
    ENode *first_edge; // 指向第一条依附该点的弧
}VNode;

typedef struct LGraph{  // 邻接表
    int vexnum; // 顶点的数目
    int edgnum; // 边的数目
    VNode vexs[MAX];
}LGraph;

LGraph *create_lgraph();

LGraph *create_lgraph_directed();

void print_graph(LGraph G);

void DFSTraverse(LGraph G);

void BFS(LGraph G);

int get_position(LGraph graph, char ch);

void link_last(ENode *list, ENode *node);

int main(){
    LGraph *G;

    G = create_lgraph();  // 创建无向图
    G = create_lgraph_directed();  // 创建有向图
    print_graph(*G); // 打印
    DFSTraverse(*G); // 深度优先
    BFS(*G); // 广度优先
    return 0;

}

void BFS(LGraph G) {
    int head = 0;
    int rear = 0;
    int queue[MAX];     // 辅组队列
    int visited[MAX];   // 顶点访问标记
    int i, j, k;
    ENode *node;

    //每个顶点未被访问
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    //从零号顶点开始遍历
    printf("BFS: ");
    for (i = 0; i < G.vexnum; i++)//对每个连同分量均调用一次BFS
    {
        if (!visited[i])//如果没访问过，就打印，同时入队,最初是A
        {
            visited[i] = 1;//标记已经访问过
            printf("%c ", G.vexs[i].data);
            queue[rear++] = i;  // 入队列
        }
        while (head != rear) //第一个进来的是A，遍历A的每一条边
        {
            j = queue[head++];  // 出队列
            node = G.vexs[j].first_edge;
            while (node != NULL)
            {
                k = node->ivex;
                if (!visited[k])
                {
                    visited[k] = 1;
                    printf("%c ", G.vexs[k].data);
                    queue[rear++] = k;//类似于树的层次遍历，遍历到的同时入队
                }
                node = node->next_edge;
            }
        }
    }
    printf("\n");
}

static void DFS(LGraph G, int i, int *visited)
{
    ENode *node;

    visited[i] = 1;//要访问当前结点了，所以打印
    printf("%c ", G.vexs[i].data);
    node = G.vexs[i].first_edge;//拿当前顶点的后面一个顶点
    while (node != NULL)
    {
        if (!visited[node->ivex])//只要对应顶点没有访问过，深入到下一个顶点访问
            DFS(G, node->ivex, visited);
        node = node->next_edge;//某个顶点的下一条边，例如B结点的下一条边
    }
}

void DFSTraverse(LGraph G) {
    int i;
    int visited[MAX];       // 顶点访问标记

    // 初始化所有顶点都没有被访问
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("DFS: ");
    //从A开始深度优先遍历
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");
}

void print_graph(LGraph G) {
    int i;
    ENode *node;

    printf("List Graph:\n");
    for (i = 0; i < G.vexnum; i++)//遍历所有的顶点
    {
        printf("%d(%c): ", i, G.vexs[i].data);
        node = G.vexs[i].first_edge;
        while (node != NULL)//把每个顶点周围的结点都输出一下
        {
            printf("%d(%c) ", node->ivex, G.vexs[node->ivex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}

LGraph* create_lgraph_directed() {
    char c1, c2;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
            {'A', 'B'},
            {'B', 'C'},
            {'B', 'E'},
            {'B', 'F'},
            {'C', 'E'},
            {'D', 'C'},
            {'E', 'B'},
            {'E', 'D'},
            {'F', 'G'}};
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    ENode *node1;
    LGraph* G;


    if ((G=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(G, 0, sizeof(LGraph));

    // 初始化"顶点数"和"边数"
    G->vexnum = vlen;
    G->edgnum = elen;
    // 初始化"邻接表"的顶点
    for(i=0; i<G->vexnum; i++)
    {
        G->vexs[i].data = vexs[i];
        G->vexs[i].first_edge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<G->edgnum; i++)
    {
        // 读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = get_position(*G, c1);
        p2 = get_position(*G, c2);
        // 初始化node1
        node1 = (ENode *)calloc(1,sizeof(ENode));
        node1->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(G->vexs[p1].first_edge == NULL)
            G->vexs[p1].first_edge = node1;
        else
            link_last(G->vexs[p1].first_edge, node1);
    }
    return G;
}

LGraph* create_lgraph() {
    char c1, c2;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
            {'A', 'C'},
            {'A', 'D'},
            {'A', 'F'},
            {'B', 'C'},
            {'C', 'D'},
            {'E', 'G'},
            {'F', 'G'}
    };
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);

    int i, p1, p2;
    ENode *node1, *node2;
    LGraph * G;

    if ((G=(LGraph*)malloc(sizeof(LGraph))) == NULL){
        return NULL;
    }
    memset(G, 0, sizeof(LGraph)); // 把申请的空间初始化为0

    // 初始化 顶点数 和 边数
    G ->vexnum = vlen;
    G ->edgnum = elen;

    // 初始化 邻接表 的顶点
    for (int i = 0; i < G ->vexnum; i++) {
        G ->vexs[i].data = vexs[i];
        G ->vexs[i].first_edge = NULL;
    }

    // 初始化 邻接表 的边
    for(int j = 0; j < G ->edgnum; j ++){
        // 读取边的起始顶点和结束顶点
        c1 = edges[j][0];
        c2 = edges[j][1];

        p1 = get_position(*G, c1); // p1 对应起始顶点的下标位置
        p2 = get_position(*G, c2); // p1 对应结束顶点的下标位置

        // 初始化node1
        node1 = (ENode *) calloc(1,sizeof(ENode));
        node1 ->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(G->vexs[p1].first_edge == NULL)
            G->vexs[p1].first_edge = node1;
        else
            link_last(G->vexs[p1].first_edge, node1);
        // 初始化node2
        node2 = (ENode*)calloc(1,sizeof(ENode));
        node2->ivex = p1;
        // 将node2链接到"p2所在链表的末尾"
        if(G->vexs[p2].first_edge == NULL){
            G->vexs[p2].first_edge = node2;
        }
        else{
            link_last(G->vexs[p2].first_edge, node2);
        }
    }
    return G;
}

void link_last(ENode *list, ENode *node) {
    ENode *p = list;
    while(p->next_edge)
        p = p->next_edge;
    p->next_edge = node;
}


int get_position(LGraph g, char ch)
{
    int i;
    for(i=0; i<g.vexnum; i++)//去顶点结构体数组中遍历每个顶点
        if(g.vexs[i].data==ch)
            return i;//返回的是对应顶点的下标
    return -1;
}
