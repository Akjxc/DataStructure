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
        while(Tail->NextNode != NULL){
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
        if((*Head) != NULL)
            (*Head)->PrevNode = NULL;

        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }
    else {
        Node* Temp = Remove;

        if(Remove->PrevNode != NULL)
            Remove->PrevNode->NextNode = Temp->NextNode;

        if(Remove->NextNode != NULL)
            Remove->NextNode->PrevNode = Temp->PrevNode;

        Remove->NextNode = NULL;
        Remove->PrevNode = NULL;
    }
}

void DLL_InsertAfter(Node* Current, Node* NewNode){
    NewNode->NextNode = Current->NextNode;
    NewNode->PrevNode = Current;

    if(Current != NULL){
        Current->NextNode = NewNode;
        Current->NextNode->PrevNode = NewNode;
    }
}

int DLL_GetNodeCount(Node* Head){
    unsigned int Count = 0; // unsigned - 음수 표현 불가, 0과 양수만
    Node* Current = Head;

    while(Current != NULL){
        Current = Current->NextNode;
        Count++;
    }

    return Count;
}

void PrintNode(Node* _Node){
    if(_Node->PrevNode == NULL)
        printf("Prev : NULL\t");
    else 
        printf("Prev : %d\t", _Node->PrevNode->Data);
    
    printf("Current : %d\t", _Node->Data);

    if(_Node->NextNode == NULL)
        printf("Next : NULL\n");
    else
        printf("Next : %d\n", _Node->NextNode->Data);
}

void PrintReverse(Node* Head){
    unsigned int Count = 0;
    Node* Tail = Head;
    while(Tail->NextNode != NULL){
        Tail = Tail->NextNode;
        Count++;
    }

    while(Tail != NULL){
        printf("List[%d] : %d\n", Count, Tail->Data);
        Tail = Tail->PrevNode;
        Count--;
    }
}

int main(void){
    Node* List = NULL;
    Node* NewNode = NULL;

    for(int i = 0; i < 5; i++){
        NewNode = DLL_CreateNode(i);
        DLL_AppendNode(&List, NewNode);
    }

    for(int i = 0; i < DLL_GetNodeCount(List); i++){
        PrintNode(DLL_GetNodeAt(List, i));
    }

    printf("-------------------------------------------\n");

    PrintReverse(List);
}