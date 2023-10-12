#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 최대 힙 구조체 정의
typedef struct {
    int* arr;   // 노드 배열
    int capacity;   // 힙의 최대 크기
    int size;       // 현재 힙의 크기
    int moves;      // 노드가 이동된 횟수
} MaxHeap;

// 최대 힙 초기화 함수
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

// 노드 추가 함수
void insert(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        printf("힙이 가득 찼습니다. 추가할 수 없습니다.\n");
        return;
    }

    // 노드를 마지막 위치에 추가
    heap->arr[heap->size] = value;

    // 노드를 부모 노드와 비교하여 올바른 위치로 이동
    int current = heap->size;
    int moved = 0; // 노드 이동 여부를 나타내는 변수
    while (current > 0 && heap->arr[current] > heap->arr[(current - 1) / 2]) {
        swap(&heap->arr[current], &heap->arr[(current - 1) / 2]);
        current = (current - 1) / 2;
        moved = 1; // 노드가 이동했음을 표시
    }

    // 노드 이동 횟수 증가 (노드가 이동했을 때만 증가)
    if (moved) {
        heap->moves++;
    }

    heap->size++;
}

// 나머지 코드는 이전 코드와 동일합니다.

// 최대 힙에서 루트 노드 삭제하는 함수
void deleteRoot(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("힙이 비어 있습니다. 삭제할 노드가 없습니다.\n");
        return;
    }

    // 루트 노드와 마지막 노드를 교환
    swap(&heap->arr[0], &heap->arr[heap->size - 1]);
    heap->size--;

    // 루트 노드를 자식 노드와 비교하여 올바른 위치로 이동
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

// 레벨별로 힙 출력하는 함수
void printLevelOrder(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("힙이 비어 있습니다. 출력할 노드가 없습니다.\n");
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

// 메인 함수
int main() {
    int capacity;
    printf("힙의 최대 크기를 입력하세요: ");
    scanf("%d", &capacity);

    MaxHeap* heap = createMaxHeap(capacity);

    // 초기 상태의 트리를 추가
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
        printf("\ni : 노드 추가\n");
        printf("d : 노드 삭제\n");
        printf("p : 레벨별 출력\n");
        printf("c : 종료\n");
        printf("메뉴 입력: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'i':
            printf("추가할 값 입력: ");
            scanf("%d", &value);
            insert(heap, value);
            moves++;
            break;
        case 'd':
            deleteRoot(heap);
            moves++;
            break;
        case 'p':
            printf("레벨별 출력:\n");
            printLevelOrder(heap);
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            free(heap->arr);
            free(heap);
            return 0;
        default:
            printf("올바른 메뉴를 선택해 주세요.\n");
        }

        printf("노드가 이동된 횟수: %d\n", moves);
    }

    return 0;
}

