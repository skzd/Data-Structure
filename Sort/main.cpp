#include <stdio.h>
#define MaxSize 1000
#define N 10

typedef struct {
    int a[MaxSize + 1];
    int length;
}SqList;

// 冒泡排序
void BubbleSort(SqList *L);
void BubbleSort2(SqList *L);

// 快速排序
void QSort(SqList *L);
void QuickSort(SqList *L, int low, int high);
int Partition(SqList *L, int low, int high);

// 输出
void print(SqList L);

int main(){

    int i;
    int d[N] = {11, 22, 33, 44, 23, 12, 29, 16, 19, 88};
    SqList l0, l1, l2, l3, l4, l5, l6, l7, l8, l9;

    for(i = 0; i < N; i ++){
        l0.a[i + 1] = d[i];
    }
    l0.length = N;
    l1 = l2 = l3 = l4 = l5 = l6 = l7 = l8 = l9 = l0;
    printf("初始化后的数组为：\t");
    print(l0);
    printf("\n");

    BubbleSort(&l1);
    printf("冒泡排序后：\t");
    print(l1);
    printf("\n");

    BubbleSort2(&l2);
    printf("冒泡排序后：\t");
    print(l2);
    printf("\n");

    QSort(&l3);
    printf("快速排序后：\t");
    print(l3);
    printf("\n");

    return 0;
}

void BubbleSort(SqList *L){
    for(int i = 0; i < L->length; i ++){
        for(int j = L->length - 1; j > i; j --){
            if(L->a[j - 1] > L->a[j]){
                int temp = L->a[j - 1];
                L->a[j - 1] = L->a[j];
                L->a[j] = temp;
            }
        }
    }
}

void BubbleSort2(SqList *L){
    for(int i = 0; i < L->length; i++){
        for(int j = 0; j < L->length - 1 - i; j ++){
            if(L->a[j] > L->a[j+1]){
                int temp = L->a[j];
                 L->a[j] = L->a[j+1];
                 L->a[j+1] = temp;
            }
        }
    }
}

void QSort(SqList *L){
    QuickSort(L, 1, L->length);
}

void QuickSort(SqList *L, int low, int high){
    if(low < high){
        int pivotpos = Partition(L, low, high);
        QuickSort(L, low, pivotpos - 1);
        QuickSort(L,  pivotpos + 1,  high);
    }
}

int Partition(SqList *L, int low, int high){
    int pivot = L->a[low];  // 将表中的第一个元素作为枢轴，对表进行划分
    while(low < high){
        while (low < high && L->a[high] >= pivot){
            high --;
        }
        L->a[low] = L->a[high];
        while(low < high && L->a[low] <= pivot){
            low ++;
        }
        L->a[high] = L->a[low]; // 枢轴元素放到最终位置
    }
    L->a[low] = pivot;
    return low; // 返回存放枢轴的最终位置
}

void print(SqList L){
    for(int i = 0; i < L.length; i++){
        printf("%d\t", L.a[i]);
    }
}
