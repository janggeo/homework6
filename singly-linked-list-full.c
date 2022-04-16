/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */

/*수정사항
	1. 처음 insertNode()를 호출할경우 리스트 생성이 안되고 종료됨 
	->headnode* headnode를 생성했지만 headnode가 가리키는 구조체가 없다. 따라서 동적할당하여 생성하고 first는 NULL로 초기화
	2. 연결리스트 앞이나 뒤에 값을 추가하거나 invert시킬 경우 리스트의 오름차순이 틀어지므로 오름차순으로 정렬하는 함수 sortList 추가
*/

#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {	/*node 구조체. key값과 다음 노드를 가리키는 포인터*/
 	int key;
	struct Node* link;
} listNode;

typedef struct Head {	/*연결리스트의 head를 가리킬 포인터 first를 가지는 구조체*/
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);	//연결리스트 초기화하는 함수
int freeList(headNode* h);			//연결리스트 동적할당을 해제 하는 함수

int insertFirst(headNode* h, int key);	//연결리스트 앞에 노드를 추가하는 함수
int insertNode(headNode* h, int key);	//연결리스트에 노드를 추가하는 함수 이때 오름차순으로 정렬된다.
int insertLast(headNode* h, int key);	//연결리스트 뒤에 노드를 추가하는 함수

int deleteFirst(headNode* h);			//연결리스트 제일앞의 노드를 제거하는 함수
int deleteNode(headNode* h, int key);	//특정한 노드를 연결리스트에서 제거하는 함수
int deleteLast(headNode* h);			//연결리스트 마지막의 노드를 제거하는 함수
int invertList(headNode* h);			//연결리스트를 역순으로 정렬하는 함수
void printList(headNode* h);			//연결리스트를 출력하는 함수

headNode* sortList(headNode* h);		//(추가)연결리스트를 오름차순으로 정렬하는 함수

int main()
{
	printf("-----[장정환] [2021076029]-----\n");
	char command;
	int key;
	headNode* headnode=NULL;	//동적할당 받은 headNode를 저장할 포인터
	headnode=(headNode*)malloc(sizeof(headNode));	//headNode를 동적할당
	headnode->first=NULL;		//아직 가리키는 값이 없으므로 first는 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Sort List     = s\n");
		printf(" Quit		   =q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);	//초기화한 연결리스트의 head를 반환
			break;
		case 'p': case 'P':
			printList(headnode);		//headnode를 인수로 주면 연결리스트를 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);			//key값을 입력받는다.
			insertNode(headnode, key);	//key값을 인수로주고 연결리스트에 오름차순으로 추가한다.
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);			//key값을 입력받는다.
			deleteNode(headnode, key);	//해당 key값을 가진 node가 연결리스트에 있으면 제거, 해제한다.
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);			//key값을 입력받는다.
			insertLast(headnode, key);	//리스트의 마지막에 노드를 추가한다.
			break;
		case 'e': case 'E':
			deleteLast(headnode);		//리스트의 마지막 노드를 제거한다.
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);	//리스트의 앞에 노드를 추가한다.
			break;
		case 't': case 'T':
			deleteFirst(headnode);		//리스트의 제일 앞 노드를 제거한다.
			break;	
		case 'r': case 'R':
			invertList(headnode);		//리스트를 역순으로 정렬한다.
			break;
		case 'q': case 'Q':
			freeList(headnode);			//리스트 동적할당을 해제한다.
			break;
		case 's': case'S':
			headnode=sortList(headnode);	//리스트를 오름차순으로 정렬한다.
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;	//first를 이동시키며 해제할경우 다음 노드를 가리킬 수 없으므로 p가 이동하도록 설정

	listNode* prev = NULL;
	while(p != NULL) {	//마지막까지 반복
		//한 노드씩 이동
		prev = p;
		p = p->link;	
		free(prev);		//prev 해제
	}
	free(h);	//headnode 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//새로운 노드 동적할당
	node->key = key;	//입력받은 key값을 할당
	node->link = NULL;	//다음 노드를 가리키는 link는 null로 초기화

	if (h->first == NULL)	//추가된 노드가 없는 경우(처음 노드를 추가하는 경우) 
	{
		h->first = node;	//새로운 노드를 head로 잡는다.
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//새로운 노드를 리스트 제일 앞에 추가
				h->first = node;	//새로운 노드를 first로 지정
				node->link = n;		//새로운 노드의 link를 n이 가리키는 노드로 지정
			} else { /* 중간이거나 마지막인 경우 */
				node->link = n;		//새로운 노드를 n과 trail사이에 추가
				trail->link = node;
			}
			return 0;
		}
		/*trail과 n을 한칸씩 옮긴다.*/
		trail = n;
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//node를 동적할당하여 key를 저장하고 link는 null로 초기화
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)	//연결리스트에 노드가 없는경우
	{
		h->first = node;	//first포인터가 바로 노드를 가리키게 한다.
		return 0;
	}

	listNode* n = h->first;		//first포인터를 이동시킬 수는 없으므로 n이라는 포인터 만든다.
	while(n->link != NULL) {	//마지막 노드 까지 반복하여 n을 마지막 노드를 가리키게 한다.
		n = n->link;
	}
	n->link = node;		//n다음에 node를 추가한다.
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//새로운 노드를 동적할당하고 key값을 저장
	node->key = key;

	node->link = h->first;	//새로운 노드의 link가 리스트의 제일 앞부분을 가리키게 한다.
	h->first = node;		//first가 새로운 노드를 가리키게 한다.

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	/*연결리스트가 비어있을경우*/
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;		/*검색할 노드를 가리키는 포인터*/
	listNode* trail = NULL;		/*검색할 노드의 바로 뒤 노드를 가리키는 포인터*/

	/* key를 기준으로 해제할 위치를 찾는다 */
	while(n != NULL) {	//연결리스트 마지막까지 찾는다
		if(n->key == key) {		//입력된 key와 같은경우 
			/*해제할 노드가 연결리스트 제일 앞 노드인경우*/
			if(n == h->first) {
				h->first = n->link;	//headenode 포인터를 다음 노드로 변경
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;	//노드포인터 n이 가리키는 노드를 제외 하고 앞뒤노드롤 연결시킨다
			}
			free(n);	//n이 가리키는 노드 해제
			return 0;
		}
		/*trail과 n을 다음 노드로 한칸씩 이동*/
		trail = n;
		n = n->link;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL;
	free(n);

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)	//리스트에 노드가 없을 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;	//first를 다음 노드로 변경.
	free(n);	//해제

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	/*변경할 노드와 변경할 노드의 앞,뒤 노드를 가리켜야하므로 총 세개의 포인터 필요*/
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;		//middle을 다음 노드를 가리키도록 변경
		n = n->link;
		middle->link = trail;	//middle이 가리키는 노드의 link 가 이전 노드를 가리키도록 변경 하여 역순으로 만든다.
	}

	h->first = middle;

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;	//p 포인터를 하나씩옮겨 모두 출력
		i++;
	}

	printf("  items = %d\n", i);	//리스트내 노드 개수 출력
}

headNode* sortList(headNode* h){	//순서가 어지러워진 리스트를 오름차순을 정렬
	if(h->first==NULL){
		printf("nothing to sort..\n");
		return 0;
	}
	listNode* a1=h->first;
	listNode* a2=h->first;
	headNode* hh=(headNode*)malloc(sizeof(headNode));
	hh->first=NULL;

	int Max;	//범위내 노드의 최대값을 저장
	while(a1->link!=NULL){
		Max=a1->key;
		while(a1->link!=NULL){	// 모든 노드를 비교 가장 큰값을 찾는다.
			a1=a1->link;
			if(a1->key>=Max){
				Max=a1->key;
			}
		}
		insertNode(hh,Max);	//새로운 headNode포인터와 최댓값을 인수로 주어 새로운 리스트를 만든다.
		deleteNode(h,Max);	//원래 리스트에서 Max값을 가지는 노드를 제거,해제
		a1=h->first;		//a1의 위치를 다시 조정
	}
	/*원래 리스트의 남은 마지막하나의 노드를 새로운 리스트로 추가하고 원래 리스트에서 제거,해제*/
	insertNode(hh,a1->key);
	deleteNode(h,a1->key);
	free(h);
	return hh;	//새로운 리스트의 headNode를 반환
}
