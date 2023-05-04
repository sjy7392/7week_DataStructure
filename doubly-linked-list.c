/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	//headNode가 NULL이 아니라면, 할당된 메모리 해제
	if(*h != NULL)
		freeList(*h);

	//headNode에 메모리를 할당한 후 리턴
	*h=(headNode*)malloc(sizeof(headNode));
	(*h)->first=NULL;
	return 1;
}

int freeList(headNode* h){
	//h와 연결된 listNode 메모리 해제
	listNode* p = h->first; //첫번째 노드를 가리키는 포인터 p 생성
	
	//전 값에 NULL 할당
	listNode* prev = NULL;
	while(p!=NULL){  //p가 NULL이 될 때까지
		prev = p; //prev에 현재 노드 할당
		p = p->rlink; //p를 다음 노드로 이동
		free(prev); //prev가 가리키는 노드의 메모리 해제
	}
	free(h); //h 메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	//리스트가 비어있을 시 아무것도 출력하지 않고 함수 종료
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	//리스트의 첫번째 노드를 가리키는 포인터 p를 h->first로 초기화
	p = h->first;

	while(p != NULL) { //p가 NULL이 아닐 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //키 값과 인덱스 값 출력
		p = p->rlink; //다음 노드로 변경
		i++; //인덱스 값 증
	}

	printf("  items = %d\n", i); //리스트에 저장된 노드 수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node
	node->key=key; //node에 key 할당
	node->rlink=NULL; //node의 오른쪽 링크에 NULL 할당
	node->llink=NULL; //node의 왼쪽 링크에 NULL 할당

	if(h->first==NULL) //h의 첫번째에 NULL 할당
	{
		h->first=node;  //h의 첫번째 값에 노드 할당
		return 0;
	}

	listNode* n = h->first; //n을 첫번째 노드로 지정
	while(n->rlink!=NULL){ //노드가 끝까지 갈 데 동안
		n = n->rlink; 
	}
	n->rlink=node;  //n의 오른쪽 링크에 node(새로 생성해서 삽입할 노드) 할당
	node->llink=n; //node의 왼쪽 링크에 n 할당
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	//h에 아무것도 들어있지 않을 경우
	if(h->first==NULL){
		printf("nothing to delete. \n");
		return 0;
	}

	//listNode형의 n에 첫번째 값 할당
	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL){ //n의 다음 링크가 비어있다면
		h->first==NULL; //h의 첫번째 값에 NULL 지정
		free(n); //n 삭제
		return 0;
	}

	while(n->rlink != NULL){ //n의 마지막 노드까지 이동
		trail=n;
		n=n->rlink;
	}

	trail->rlink=NULL; //이전 노드의 다음 NULL 할당
	free(n); //n 삭제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 생성
	node->key = key; //node의 key에 값 할당
	node->rlink = node->llink = NULL; //node의 전, 후 값에 NULL 할당

	if(h->first==NULL){ //h에 값이 존재하지 않으면
		h->first=node; //첫번째에 node 할당
		return 1;
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h->first==NULL) //노드가 존재하지 않으면
	{
		printf("nothing to delete.\n"); //출력
		return 0;
	}
	listNode* n = h->first; //첫번째 노드를 가리키는 포인터 n 생성
	h->first = n->rlink; //h의 첫번째 노드를 n의 다음 노드로

	free(n); //n 삭제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first==NULL){ //리스트에 아무런 값도 존재하지 않으면
		printf("nothing to invert...\n"); //출력문 출력
		return 0;
	}
	listNode *n = h->first; //n에 첫번째 값 할당
	listNode *trail = NULL; //전 값을 NULL로 초기화
	listNode *middle = NULL; //중간 값을 NULL로 초기화
	
	while(n != NULL){ //n이 NULL이 아닐 때까지
		trail = middle; //trail에 middle값 저장
		middle = n; //middle에 현재 노드 저장
		n = n -> rlink; //n을 다음 노드로 이동
		middle->rlink = trail; //middle의 우측 노드를 이전 노드로 설정
		middle -> llink = n; //middle의 좌측 노드를 다음 노드로 설정
	}

	h->first = middle; //리스트의 첫번째 노드를 middle로 설정

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 생성
	node->key = key; //node의 key에 값 할당
	node->rlink = node->llink = NULL; //node의 전, 후 값에 NULL 할당

	if(h->first==NULL){ //값이 존재하지 않을 경우
		h->first = node; //첫번째 값을 노드로 설정
		return 0;
	}

	listNode* n = h->first; //첫번째 노드를 가리키는 포인터 n 생성

	while(n != NULL){ //마지막 노드까지
		if(n->key >= key){ //기존 노드가 삽입하려는 값보다 크면
			if(n == h->first){ //n이 첫번째 값과 같으면
				insertFirst(h, key); //맨 앞에 h 삽입
			} else{ //중간이나 마지막에 삽입하는 경우엔
				node->rlink=n; //노드의 다음 값을 n으로
			}
			return 0;
		}
		n=n->rlink; //n에 n 다음 값 할당
	}

	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	//h에 아무것도 들어있지 않을 경우
	if(h->first==NULL){
		printf("nothing to delete. \n");
		return 0;
	}

	//listNode형의 n에 첫번째 값 할당
	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { //첫 노드째 노드일 경우
				deleteFirst(h);
			} else if (n->rlink == NULL){ //마지막 노드일 경우
				deleteLast(h);
			} else { //중간 값일 경우
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key); //값을 찾지 못했을 때 출력
	return 1;
}


#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, j, count=1;

	printf("행과 열을 입력하시오: ");
	scanf("%d %d", &i, &j);

	int **matrix = (int **)malloc(i*sizeof(int*));
	for(int r=0; r<i; r++){
		matrix[r]=(int *)malloc(j*sizeof(int));
	}

	for(int r=0; r<i; r++){
		for(int c=0; c<j; c++){
			matrix[r][c]=count;
			count++;
		}
	}

	for(int r=0; r<i; r++){
		for(int c=0; c<j; c++){
			printf("%d ", matrix[r][c]);
		}
	}

	for(int r=0; r<i; r++){
		free(matrix[r]);
	}
	free(matrix);
	
}