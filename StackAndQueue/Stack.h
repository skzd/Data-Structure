#define MaxSize 50
#define ElemType int

typedef struct {
    ElemType data[MaxSize]; // 存在栈中的元素
    int top;    // 栈顶元素
}SqStack;

/**
 * 初始化
 * @param S
 */
void InitStack(SqStack &S){
    S.top = -1;
}

/**
 * 栈判空
 * @param S
 * @return
 */
bool StackEmpty(SqStack S){
    if (S.top == -1){
        return true;
    } else{
        return false;
    }
}

/**
 * 进栈
 * @param S
 * @param x
 * @return
 */
bool Push(SqStack &S, ElemType x){
    if(S.top == MaxSize - 1){   // 栈满
        return false;
    }
    S.data[++ S.top] = x;
    return true;
}

/**
 * 出栈
 * @param S
 * @param x
 * @return
 */
bool Pop(SqStack &S, ElemType &x){
    if(S.top == -1){    // 栈空
        return false;
    }
    x = S.data[S.top --];
    return true;
}

/**
 * 读取栈顶元素
 * @param S
 * @param x
 * @return
 */
bool GetTop(SqStack S, ElemType &x){
    if(S.top == -1){
        return false;
    }
    x = S.data[top];    // x记录栈顶元素
    return true;
}

