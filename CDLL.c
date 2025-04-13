#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode {
    ElementType Data;
    struct tagNode* PrevNode;
    struct tagNode* NextNode;
} Node;

Node* CDLL_CreateNode(ElementType NewData){
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->PrevNode = NULL;
    NewNode->NextNode = NULL;

    return NewNode;
}

Node* CDLL_DestroyNode(Node* Node){
    free(Node);
}

void CDLL_AppendNode(Node** Head, Node* NewNode){
    if((*Head) == NULL){
        *Head = NewNode;
        (*Head)->PrevNode = *Head;
        (*Head)->NextNode = *Head;
    }
    else {
        Node* Tail = (*Head)->PrevNode;

        Tail->NextNode->PrevNode = NewNode;
        Tail->NextNode = NewNode;

        NewNode->NextNode = *Head;
        NewNode->PrevNode = Tail;
    }
}

void CDLL_RemoveNode(Node** Head, Node* Remove){
    if((*Head) == Remove){
        (*Head)->PrevNode->NextNode = Remove->NextNode;
        (*Head)->NextNode->PrevNode = Remove->PrevNode;

        *Head = Remove->NextNode;

        Remove->NextNode = NULL;
        Remove->PrevNode = NULL;
    }
    else{
        Remove->PrevNode->NextNode = Remove->NextNode;
        Remove->NextNode->PrevNode = Remove->PrevNode;

        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }
}

int main(void){

}