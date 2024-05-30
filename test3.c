#include <stdio.h>

#define MAX_SIZE 100 // 定义线性表的最大长度

// 定义线性表的结构体
typedef struct {
    int data[MAX_SIZE]; // 用数组存储线性表的元素
    int length; // 记录线性表的当前长度
} LinearList;

// 初始化线性表
void initList(LinearList *list) {
    list->length = 0; // 将线性表的长度初始化为0
}

// 向线性表中插入元素
int insertElement(LinearList *list, int index, int element) {
    if (index < 0 || index > list->length || list->length == MAX_SIZE) {
        // 插入位置无效或者线性表已满，插入失败
        return 0;
    }
    
    // 将index后的元素向后移动一位
    for (int i = list->length - 1; i >= index; i--) {
        list->data[i + 1] = list->data[i];
    }
    
    // 将新元素插入到index位置
    list->data[index] = element;
    list->length++; // 线性表长度加1
    return 1; // 插入成功
}

// 打印线性表中的元素
void printList(LinearList *list) {
    printf("Linear List: ");
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main() {
    LinearList list;
    initList(&list);
    
    // 向线性表中插入元素
    insertElement(&list, 0, 1);
    insertElement(&list, 1, 2);
    insertElement(&list, 2, 3);
    
    // 打印线性表中的元素
    printList(&list);
    
    return 0;
}
 