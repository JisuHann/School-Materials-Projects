/* symtable.c - 각 identifier의 Hash Table 구성
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"
#define STsize 1000
#define HTsize 100 
#define Isize 25 
#define isWord(x) ((((x>='a'&&(x)<='z') || ((x)>='A'&&(x)<='Z')) || (x=='_') )
#define isNum(x) ((x) >= '0' && (x) <= '9')
#define idlen 12 

typedef enum errorTypes ERRORtypes;
ERRORtypes errr;
typedef struct HTentry* HTpointer;
typedef struct HTentry
{
	int index;
	HTpointer next;
} HTentry;

char separators[] = " \t\r\n";
HTpointer HT[HTsize];
char ST[STsize];
int nid = 0;
int nfree = 0;
int sameid = 0;
int flag = 0;
int EOFflag = 1;
int initalize_done = 0;

char input;
char string[Isize];
int hashcode;
extern void reporterror(char* string);

//ReadIO 함수: string 읽어서 ST에 넣기(overfl 에러 체크)
void ReadID(char* string)
{
	nid = nfree;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (nfree >= STsize) //STSize overflow
		{
			errr = overfl;
			printerror(errr, string);
			break;
		}
		else {
			ST[nfree++] = string[i];
		}
	}
}

//ComputeHS 함수: ST에 존재하는 [nid~(nfree-2)]까지의 character를 이용한 해시함수 구현
//               H(x) = (f(x) mod m)+1
void ComputeHS(int nid, int nfree)
{
	int tot_ascii = 0;
	for (int i = nid; i < nfree - 1; i++)
		tot_ascii += (int)ST[i];
	hashcode = tot_ascii % HTsize;
}

// LookupHS: identifier의 해시 결과 중복 발생 여부에 따라 flag 값 조정
void LookupHS(int nid, int hscode)
{
	HTpointer temp;
	int a, b;
	flag = 0;

	if (HT[hscode] != NULL) {
		temp = HT[hscode];
		while (temp != NULL && flag == 0) {
			flag = 1;
			a = temp->index;
			b = nid;
			sameid = a;

			while (ST[a] != '\0' && flag == 1) {
				//중복 발생
				if (ST[a] == ST[b]) {
					a++;
					b++;
				}
				//중복되지 않을 경우
				else flag = 0;
			}
			temp = temp->next;
		}
	}
}

// ADDHT 함수: HTpointer 할당 받아서 HS의 hscode에 identifier 삽입
void ADDHT(int hscode)
{
	HTpointer pt;
	pt = (HTpointer)malloc(sizeof(pt));
	pt->index = nid;
	pt->next = HT[hscode];
	HT[hscode] = pt;
}

// symtable 함수: Hash Table 전체 시스템 구성 (ReadID -> ComputerHS -> LookupHS -> ADDDHT)
void symtable(char* string) {
	int i;
	ReadID(string);
	ST[nfree++] = '\0';
	ComputeHS(nid, nfree);
	LookupHS(nid, hashcode);

	if (!flag) {
		printf("%-11d\t", nid);
		i = nid;
		while (i < nfree - 1) printf("%c", ST[i++]);
		ADDHT(hashcode);
	}
	else {
		printf("%-11d\t", sameid);
		i = nid;
		while (i < nfree - 1) printf("%c", ST[i++]);
		nfree = nid;
	}
}

// PrintHStable 함수: HashTable 결괏값 출력 - hashcode, identifier list와 전체 character 출력
void PrintHStable()
{
	printf("[[ HASH TABLE ]]\n\n");

	int i = 0;
	while (i < HTsize) {
		if (HT[i] != NULL) {
			printf("Hash code %-3d: ", i); 
			HTpointer pt = HT[i];
			while (pt != NULL) {

				int st_index = pt->index;
				while (ST[st_index] != '\0' && st_index < STsize) printf("%c", ST[st_index++]);
				printf(" ");
				pt = pt->next;
			}
			printf("\n");
		}
		i++;
	}
	printf("\n<%d characters are used in the string table>\n", nfree); 
}


