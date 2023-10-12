#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// �ִ� �� ����ü ����
typedef struct {
    int* arr;   // ��� �迭
    int capacity;   // ���� �ִ� ũ��
    int size;       // ���� ���� ũ��
    int moves;      // ��尡 �̵��� Ƚ��
} MaxHeap;

// �ִ� �� �ʱ�ȭ �Լ�
MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->moves = 0;
    heap->arr = (int*)malloc(sizeof(int) * capacity);
    return heap;
}
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ��� �߰� �Լ�
void insert(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("���� ���� á���ϴ�. �߰��� �� �����ϴ�.\n");
        return;
    }

    // ��带 ������ ��ġ�� �߰�
    heap->arr[heap->size] = value;

    // ��带 �θ� ���� ���Ͽ� �ùٸ� ��ġ�� �̵�
    int current = heap->size;
    int moved = 0; // ��� �̵� ���θ� ��Ÿ���� ����
    while (current > 0 && heap->arr[current] > heap->arr[(current - 1) / 2]) {
        swap(&heap->arr[current], &heap->arr[(current - 1) / 2]);
        current = (current - 1) / 2;
        moved = 1; // ��尡 �̵������� ǥ��
    }

    // ��� �̵� Ƚ�� ���� (��尡 �̵����� ���� ����)
    if (moved) {
        heap->moves++;
    }

    heap->size++;
}

// ������ �ڵ�� ���� �ڵ�� �����մϴ�.

// �ִ� ������ ��Ʈ ��� �����ϴ� �Լ�
void deleteRoot(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("���� ��� �ֽ��ϴ�. ������ ��尡 �����ϴ�.\n");
        return;
    }

    // ��Ʈ ���� ������ ��带 ��ȯ
    swap(&heap->arr[0], &heap->arr[heap->size - 1]);
    heap->size--;

    // ��Ʈ ��带 �ڽ� ���� ���Ͽ� �ùٸ� ��ġ�� �̵�
    int current = 0;
    while (1) {
        int leftChild = 2 * current + 1;
        int rightChild = 2 * current + 2;
        int largest = current;

        if (leftChild < heap->size && heap->arr[leftChild] > heap->arr[largest]) {
            largest = leftChild;
        }
        if (rightChild < heap->size && heap->arr[rightChild] > heap->arr[largest]) {
            largest = rightChild;
        }

        if (largest != current) {
            swap(&heap->arr[current], &heap->arr[largest]);
            current = largest;
        }
        else {
            break;
        }
    }
}

// �������� �� ����ϴ� �Լ�
void printLevelOrder(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("���� ��� �ֽ��ϴ�. ����� ��尡 �����ϴ�.\n");
        return;
    }

    int level = 0;
    int levelNodes = 1;
    int i;
    for (i = 0; i < heap->size; i++) {
        if (i == levelNodes) {
            printf("\n");
            levelNodes = levelNodes * 2;
            level++;
        }
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

// ���� �Լ�
int main() {
    int capacity;
    printf("���� �ִ� ũ�⸦ �Է��ϼ���: ");
    scanf("%d", &capacity);

    MaxHeap* heap = createMaxHeap(capacity);

    // �ʱ� ������ Ʈ���� �߰�
    insert(heap, 90);
    insert(heap, 89);
    insert(heap, 70);
    insert(heap, 36);
    insert(heap, 75);
    insert(heap, 63);
    insert(heap, 65);
    insert(heap, 21);
    insert(heap, 18);
    insert(heap, 15);

    char choice;
    int value;
    int moves = 0;

    while (1) {
        printf("\ni : ��� �߰�\n");
        printf("d : ��� ����\n");
        printf("p : ������ ���\n");
        printf("c : ����\n");
        printf("�޴� �Է�: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf("%d", &value);
            insert(heap, value);
            moves++;
            break;
        case 'd':
            deleteRoot(heap);
            moves++;
            break;
        case 'p':
            printf("������ ���:\n");
            printLevelOrder(heap);
            break;
        case 'c':
            printf("���α׷��� �����մϴ�.\n");
            free(heap->arr);
            free(heap);
            return 0;
        default:
            printf("�ùٸ� �޴��� ������ �ּ���.\n");
        }

        printf("��尡 �̵��� Ƚ��: %d\n", moves);
    }

    return 0;
}

