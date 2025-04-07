#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode {
    ElementType Data;
    struct tagNode* PrevNode;
    struct tagNode* NextNode;
} Node;

Node* DLL_CreateNode(ElementType NewData){
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->PrevNode = NULL;
    NewNode->NextNode = NULL;

    return NewNode;
}

void DLL_DestroyNode(Node* Node){
    free(Node);
}

void DLL_AppendNode(Node** Head, Node* NewNode){
    if(*Head == NULL){
        *Head = NewNode;
    }
    else {
        Node* Tail = *Head;
        while(Tail->NextNode != NULL);{
            Tail = Tail->NextNode;
        }
        Tail->NextNode = NewNode;
        NewNode->PrevNode = Tail;
    }
}

Node* DLL_GetNodeAt(Node* Head, int Location){
    Node* Current = Head;

    while(Current != NULL && (--Location) >= 0){
        Current = Current->NextNode;
    }

    return Current;
}

void DLL_RemoveNode(Node** Head, Node* Remove){
    if(*Head == Remove){
        *Head = Remove->NextNode;
    }
    else {
        (Remove->PrevNode)->NextNode = Remove->NextNode;
        (Remove->NextNode)->PrevNode = Remove->PrevNode;
        Remove->NextNode = NULL;
        Remove->PrevNode = NULL;
    }
}

int main(void){

}