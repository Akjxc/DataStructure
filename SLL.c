#include <stdio.h>
#include <stdlib.h>

// https://velog.io/@profile_exe/CMake-environment-configuration - g++ 및 Cmake 환경설정

typedef int ElementType;

typedef struct tagNode {
  ElementType Data;
  struct tagNode* NextNode;
} Node;

Node* SLL_CreateNode(ElementType NewData){
  Node* NewNode = (Node*)malloc(sizeof(Node)); 
  /*
  sizeof(Node)와 sizeof(Node*)의 결과는 어떻게 다를까요?
  내 생각 : 전자에서의 인자값은 노드 그 자체를 지칭하므로 노드의 크키값이 출력될 것이다.
          하지만 후자에서의 인자값은 노드의 메모리 주소를 지칭하는 것인데, 주소값을 크기로 결정할 수 없어서
          에러가 발생할 것이다.
  GPT : sizeof(Node) - Node 구조체 전체의 크기를 반환. 즉 노드 구조체는 노드에 저장된 자체 데이터 값과 
        다음 노드에 대한 포인터로 구성됨. 따라서 sizeof(Node)는 
        정수형 데이터(ElementType) 크기(int) + 포인터 크기의 합이 됨.
        int는 4바이트, 포인터는 32비트 시스템에서는 4바이트 / 64비트에서는 8바이트 -> 8 or 12 bytes 출력
        
        sizeof(*Node) - Node*는 포인터 변수의 크기 반환. 포인터의 크기는 주소를 저장하는 데 필요한 
        메모리 크기로 결정됨. 
        * 주소값 자체가 아니라 주소값을 저장하는 데 필요한 크기(바이트 수)가 반환됨. 
        따라서 에러가 발생하지 않고 정상적으로 크기 값이 반환됨. -> 4 or 8 bytes 출력 
  */

  NewNode->Data = NewData;
  NewNode->NextNode = NULL;

  return NewNode;
}

void SLL_DestroyNode(Node* Node){
  free(Node);
}

void SLL_AppendNode(Node** Head, Node* NewNode){
  /*
  Q. 왜 '*'가 아니고 '**'일까?
  A. C언어는 함수의 매개변수를 전달할때 기본적으로 값에 의한 전달(Call by value)
  따라서 Node* Head일 경우 노드를 가리키는 포인터 List는 복사되어 인자로 전달됨 
  -> 복사된 포인터 Head를 변경해도 원본 List는 변경 X
  List라는 노드를 가리키는 포인터를 수정하려면 노드를 가리키는 포인터(List)를 가리키는 포인터를 인자로 받음
  -> 즉 List를 가리키는 "주소" 전달됨, List의 원본에 접근 가능
  "첫번째 매개변수를 Node**로 선언하면 Head 포인터 자신의 주소를 넘길 수 있게 됩니다. Head 포인터는 List 포인터 변수의 '주소'를 가리키고, 이 주소를 이용하여 List가 NewNode의 주소를 가리키도록 하는 것입니다."
  */
  if((*Head) == NULL){
    *Head = NewNode;
  }
  else {
    Node* Tail = (*Head);
    while (Tail->NextNode != NULL){
      Tail = Tail->NextNode;
    }
    Tail->NextNode = NewNode;
  }
}

Node* SLL_GetNodeAt(Node* Head, int Location){
  Node* Current = Head;

  while(Current != NULL && (--Location) >= 0){
      Current = Current->NextNode;
  }

  return Current;
}

void SLL_RemoveNode(Node** Head, Node* Remove){
  if(*Head == Remove){
    *Head = Remove->NextNode;
  }
  else{
    Node* Current = *Head;
    while(Current != NULL && Current->NextNode != Remove){
      Current = Current->NextNode;
    }

    if(Current != NULL){
      Current->NextNode = Remove->NextNode;
    }
  }
}

void SLL_InsertAfter(Node* Current, Node* NewNode){
  NewNode->NextNode = Current->NextNode;
  Current->NextNode = NewNode;
}

void SLL_InsertNewHead(Node** Head, Node* NewHead){
  if(Head == NULL){
    *Head = NewHead;
  }
  else {
    NewHead->NextNode = *Head;
    *Head = NewHead;
  }
}

int SLL_GetNodeCount(Node* Head){
  int Count = 0;
  Node* Current = Head;

  while(Current != NULL){
    Current = Current->NextNode;
    Count++;
  }

  return Count;
}

// Quiz 1-2
void SLL_InsertBefore(Node** Head, Node* Current, Node* NewNode){
  while(Head != NULL && (*Head)->NextNode != Current){
    *Head = (*Head)->NextNode;
  }
  (*Head)->NextNode = NewNode;
  NewNode->NextNode = Current;
}

//GPT 사용함
void SLL_DestroyAllNodes(Node** Head){
  while(*Head != NULL){
    Node* Current = *Head; // 항상 첫번째 노드 가져옴 - 리스트를 가져온다는 것은 리스트의 헤드를 가져오는 것.
    SLL_RemoveNode(Head, Current);
    free(Current);
  }
}
// 내가 작성한 코드 : 
// SLL_GetNodeCount(*List)는 처음에는 올바른 개수를 반환하지만, SLL_RemoveNode()가 실행될 때마다 리스트 크기가 줄어듦.
// 하지만 for 루프에서 초기 리스트 개수만큼 반복하려고 시도함. 즉, 리스트 크기가 줄어들면서 i 값이 SLL_GetNodeCount(*List)보다 커지게 됨.
// 따라서 마지막 노드가 삭제되지 않았던 것.
// void SLL_DestroyAllNodes(Node** List){
//   Node* Current;

//   for(int i = 0; i < SLL_GetNodeCount(*List); i++){
//     Current = SLL_GetNodeAt(*List, 0);
//     SLL_RemoveNode(List, Current);
//   }
// }

int main(void) {
  /* <노드 추가>
  Node* List = NULL;
  Node* NewNode = NULL;
  NewNode = SLL_CreateNode(117);
  SLL_AppendNode(&List, NewNode);
  NewNode = SLL_CreateNode(119);
  SLL_AppendNode(&List, NewNode);
  */

  // 노드 탐색
  // Node* List = NULL;
  // Node* MyNode = NULL;

  // SLL_AppendNode(&List, SLL_CreateNode(117));
  // SLL_AppendNode(&List, SLL_CreateNode(119));

  // MyNode = SLL_GetNodeAt(List, 0);
  // printf("%d\n", MyNode->Data);
  
  // 노드 삭제
  // Node* List = NULL;
  // Node* MyNode = NULL;

  // SLL_AppendNode(&List, SLL_CreateNode(117));
  // SLL_AppendNode(&List, SLL_CreateNode(119));
  // SLL_AppendNode(&List, SLL_CreateNode(212));

  // MyNode = SLL_GetNodeAt(List, 1);
  // printf("%d\n", MyNode->Data);

  // SLL_RemoveNode(&List, MyNode);

  // SLL_DestroyNode(MyNode);

  //Quiz 1-2 test
  Node* List = NULL;
  Node* MyNode = NULL;

  SLL_AppendNode(&List, SLL_CreateNode(1));
  SLL_AppendNode(&List, SLL_CreateNode(2));

  printf("삽입 전\n");
  for(int i=0; i < SLL_GetNodeCount(List); i++){
    Node* Current = SLL_GetNodeAt(List, i);
    printf("List[%d] : %d\t", i, Current->Data);
  }
  printf("\n");

  MyNode = SLL_CreateNode(150);
  SLL_InsertBefore(&List, SLL_GetNodeAt(List, 1), MyNode);

  printf("삽입 후\n");
  for(int i=0; i < SLL_GetNodeCount(List); i++){
    Node* Current = SLL_GetNodeAt(List, i);
    printf("List[%d] : %d\t", i, Current->Data);
  }
  printf("\n");

  SLL_DestroyAllNodes(&List);

  printf("노드 전체 삭제 후\n");
  for(int i=0; i < SLL_GetNodeCount(List); i++){
    Node* Current = SLL_GetNodeAt(List, i);
    printf("List[%d] : %d\t", i, Current->Data);
  }
  printf("\n");  
}