#define MaxSize 50
#define ElemType int

typedef struct {
    ElemType data[MaxSize];
    int front,rear; // 队头指针和队尾指针
}SqQueue;

// 初始化
void InitQueue(SqQueue &Q){
    Q.rear = Q.front = 0;
}

//队判空
bool QueueIsEmpty(SqQueue Q){
    if(Q.front == Q.rear){
        return false;
    } else{
        return true;
    }
}

// 入队
bool EnQueue(SqQueue &Q, ElemType e){
    if((Q.rear + 1) % MaxSize == Q.front){  // 队满报错
        return false;
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;    // 队尾指针加1取模
    return true;
}

// 出队
bool DeQueue(SqQueue &Q, ElemType e){
    if(Q.rear == Q.front){
        return false;
    }
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) %MaxSize;
    return true;
}

