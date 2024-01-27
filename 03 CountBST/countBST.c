#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 3;
int nFac = 0;
int * preOrderList = NULL;
int preOrderIdx = 0;

typedef struct Node Node;

struct Node {
    int key;
    Node * left; 
    Node * right;
};

void printArray(int * arr, int n) {
    printf("[");
    for(int i=0; i<n; i++) printf("%d%s", arr[i], (i == n-1 ? "" : ", ")); 
    printf("]\n");
}

void treePush(Node * root, int n) {

    Node ** nodeToInsert = NULL;
    while(root != NULL) {
        if (n < root->key) {
            nodeToInsert = &root->left;
            root = root->left;
        }
        else {
            nodeToInsert = &root->right;
            root = root->right;
        }
    }
    root = (Node *) malloc(sizeof(Node));
    root->key = n; root->left = NULL; root->right = NULL;
    *nodeToInsert = root;
}

int calculateEncodedPreOrder(int oldValue, int newNode) {
    int reverse = 0;
    while(newNode) {
        reverse *= 10;
        reverse += newNode % 10;
        newNode /= 10;
    }
    while(reverse) {
        oldValue *= 10;
        oldValue += reverse % 10;
        reverse /= 10;
    }
    return oldValue;
}

int treePreOrder(Node * root) {
    if (root == NULL) return 0;
    int preOrder = 0;
    preOrder = calculateEncodedPreOrder(preOrder, root->key);
    preOrder = calculateEncodedPreOrder(preOrder, treePreOrder(root->left));
    preOrder = calculateEncodedPreOrder(preOrder, treePreOrder(root->right));

    return preOrder;
}

void deleteTree(Node * root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void calculateTreeOf(int * arr, int n) {
    // printArray(arr, n);
    Node * root = (Node *) malloc(sizeof(Node));
    root->key = arr[0]; root->left = NULL; root->right = NULL;
    for(int i=1;i<n;i++) {
        treePush(root, arr[i]);
    }
    preOrderList[preOrderIdx++] = treePreOrder(root);
    deleteTree(root);
}

void permuteArray(int * arr, int n) {
    if (n == N) { calculateTreeOf(arr, n); return; }
    for(int i=1; i<=N; i++) {
        int isInArray = 0;
        for(int j=0; j<n; j++) isInArray += (arr[j] == i);
        if (isInArray) continue;
        int * newArr = (int *) malloc((n + 1) * sizeof(int)); // Free +2
        for(int j=0; j<n; j++) newArr[j] = arr[j]; newArr[n] = i;
        permuteArray(newArr, n + 1);
        free(newArr);
    }
}

int factorial(int n) {
    int result = 1;
    while(n) result *= n--;
    return result;
}

void radixSort(int digit) {
    // printf("%d\n", digit);
    if (digit == N) return;
    int * bucket[10];
    for(int i=0; i<10; i++) bucket[i] = (int*) malloc(sizeof(int) * nFac);
    int bucketIdx[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int * newList = (int *) malloc(sizeof(int) * nFac);
    int newListIdx = 0;
    int magnitude = 1;
    for(int i=0; i<digit; i++) magnitude *= 10;
    for(int i=0; i<nFac; i++) {
        int num = (preOrderList[i] % (magnitude * 10)) / magnitude;
        bucket[num][bucketIdx[num]++] = preOrderList[i];
    }

    for(int i=0; i<10; i++){
        // printf("%d: ", i); printArray(bucket[i], bucketIdx[i]); printf("\n");
        for(int j=0; j<bucketIdx[i]; j++)
            newList[newListIdx++] = bucket[i][j];
        free(bucket[i]);
    }
    
    free(preOrderList);
    preOrderList = newList;
    radixSort(digit + 1);
}

int main()
{
    int * baseArr = NULL;
    nFac = factorial(N);
    preOrderList = (int *) malloc(sizeof(int) * nFac);
    permuteArray(baseArr, 0);
    radixSort(0);
    printArray(preOrderList, preOrderIdx);
    for(int i=0; i<nFac; i++) printf(i > 0 && preOrderList[i] == preOrderList[i+1] ? "" : "%d ", preOrderList[i]);
}