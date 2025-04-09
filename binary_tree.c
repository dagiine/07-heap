#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

/* Модонд элемент нэмэх */
void add(Tree *tree, int a) {
    if (tree->nodes < MAX_NODES) {
        tree->values[tree->nodes] = a;
        tree->nodes++;
    }
}

/* Модноос элементийн утгаар байрлалыг олох (хүснэгтэн дэх дугаар) */
int nodeLoc(Tree *tree, int x) {
    for (int i = 0; i < tree->nodes; i++) {
        if (tree->values[i] == x) {
            return i;
        }
    }
    return -1;
}

/* Модны эхний элементийн утга буцаах */
int root(Tree *tree) {
    if (tree->nodes > 0) {
        return tree->values[0];
    } else {
        return -1;
    }
}

/* Модны өндөр олох
 * Дамжуулсан элементээс эхэлж тооцно */
int height(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1) {
        return 0;
    }

    int left = 2 * x + 1;
    int right = 2 * x + 2;

    int lHeight, rHeight;
    
    if (left < tree->nodes) {
        lHeight = height(tree, tree->values[left]);
    } else {
        lHeight = 0;
    }
    
    if (right < tree->nodes) {
        rHeight = height(tree, tree->values[right]);
    } else {
        rHeight = 0;
    }

    if (lHeight > rHeight) {
        return 1 + lHeight;
    } else {
        return 1 + rHeight;
    }
}

/* Модны түвшин
 * Дамжуулсан элементээс эхэлж тооцно */
int level(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1) {
        return -1;
    }

    int levelCount = 0;
    while (x > 0) {
        x = (x - 1) / 2;
        levelCount++;
    }
    return levelCount;
}

/* Дамжуулсан элементийн эцэг нэгт элементийн индексийг олох */
int sibling(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1 || x == 0) {
        return -1;
    }

    int parentId = (x - 1) / 2;

    if (2 * parentId + 1 == x && 2 * parentId + 2 < tree->nodes) {
        return 2 * parentId + 2;
    }

    if (2 * parentId + 2 == x && 2 * parentId + 1 < tree->nodes) {
        return 2 * parentId + 1;
    }

    return -1;
}

/* Дамжуулсан элементийн эцгийн индексийг олох */
int parent(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x <= 0) {
        return -1;
    }
    return (x - 1) / 2;
}

/* Дамжуулсан элементийн бүх эцгийг хэвлэх */
void parents(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1) {
        return;
    }

    while (x > 0) {
        x = (x - 1) / 2;
        printf("%d\n", tree->values[x]);
    }
    printf("\n");
}

/* Pre-order traversal */
void preorder(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1) {
        return;
    }
    printf("%d\n", tree->values[x]);

    int left = 2 * x + 1;
    int right = 2 * x + 2;

    if (left < tree->nodes) {
        preorder(tree, tree->values[left]);
    }
    if (right < tree->nodes) {
        preorder(tree, tree->values[right]);
    }
}

/* In-order traversal */
void inorder(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1) {
        return;
    }

    int left = 2 * x + 1;
    int right = 2 * x + 2;

    if (left < tree->nodes) {
        inorder(tree, tree->values[left]);
    }
    printf("%d\n", tree->values[x]);
    if (right < tree->nodes) {
        inorder(tree, tree->values[right]);
    }
}

/* Post-order traversal */
void postorder(Tree *tree, int value) {
    int x = nodeLoc(tree, value);
    if (x == -1) {
        return;
    }

    int left = 2 * x + 1;
    int right = 2 * x + 2;

    if (left < tree->nodes) {
        postorder(tree, tree->values[left]);
    }
    if (right < tree->nodes) {
        postorder(tree, tree->values[right]);
    }
    printf("%d\n", tree->values[x]);
}

/* Хоёр хувьсагчийн утга солих */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Heap байгуулах
 * мод болон оруулах элементүүдийг агуулсан хүснэгт, хүснэгтийн хэмжээ
 */
void buildHeap(Tree *tree, int *arr, int size) {
    tree->nodes = size;
    for (int i = 0; i < size; i++) {
        tree->values[i] = arr[i];
    }

    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapifyDown(tree, i);
    }
}

/*
 * Heapify Up
 * мод болон heapify up гүйцэтгэж эхлэх индекс
 */
void heapifyUp(Tree *tree, int index) {
    if (index != 0) {
        int parent = (index - 1) / 2;
        if (tree->values[parent] < tree->values[index]) {
            swap(&tree->values[parent], &tree->values[index]);
            heapifyUp(tree, parent);
        }
    }
}    

/*
 * Heapify Down
 * мод болон heapify down гүйцэтгэж эхлэх индекс
 */
void heapifyDown(Tree *tree, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int max;

    if (right >= tree->nodes) {
        if (left >= tree->nodes) {
            return;
        } else {
            max = left;
        }
    } else {
        if (tree->values[left] > tree->values[right]) {
            max = left;
        } else {
            max = right;
        }
    }

    if (tree->values[index] < tree->values[max]) {
        swap(&tree->values[index], &tree->values[max]);
        heapifyDown(tree, max);
    }
}

/*
 * Heap-д элемент оруулах
 * add()-с ялгаатай нь элементээ нэмчихээд, зөв байрлалд нь оруулна
 * мод болон оруулах утга
 */
void heapInsert(Tree *tree, int value) {
    if (tree->nodes >= MAX_NODES) {
        return;
    }

    tree->values[tree->nodes] = value;
    tree->nodes++;

    heapifyUp(tree, tree->nodes - 1);
}

/*
 * Heap-с элемент гаргах
 * гарсан элементийн утгыг буцаана
 */
int heapOut(Tree *tree) {
    if (tree->nodes == 0) {
        return -1;
    }

    int rootValue = tree->values[0];
    tree->values[0] = tree->values[tree->nodes - 1];
    tree->nodes--;

    heapifyDown(tree, 0);

    return rootValue;
}