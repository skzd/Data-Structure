#define ElemType int

// 链式队列结点
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;

// 链式队列
typedef struct {
    LinkNode *front, *rear; // 队列的队头和队尾指针
}LinkQueue;

// 初始化
void InitLinkQueue(LinkQueue &Q){
    Q.front = Q.rear = (LinkNode *)malloc(sizeof (LinkNode));   // 建立头结点
    Q.front -> next = NULL; // 初始为空
}

// 判队空
bool IsEmpty(LinkQueue Q){
    if(Q.front == Q.rear){
        return true;
    } else{
        return false;
    }
}

// 入队
bool EnLinkQueue(LinkQueue &Q, ElemType e){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s -> data = e;
    s -> next = NULL;
    Q.rear ->next = s;

}

// 出队
bool DeLinkQueue(LinkQueue &Q, ElemType &e){
    if(Q.front == Q.rear){
        return false;
    }
    LinkNode *p = Q.front -> next;
    x = p -> data;
    Q.front -> next = p -> next;
    if(Q.rear == p){
        Q.rear = Q.front;   // 若原队列中只有一个结点，删除后变成空
    }
    free(p);
    return true;
}