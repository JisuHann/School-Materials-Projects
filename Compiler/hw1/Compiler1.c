/**************************************************************************************************************************** *** *
 * SymbolTable Implementation (STsize = 1000)
Contributors : Team 01(박기은, 이혜인, 한지수)
Date: 2021-03-27
입력 :
        " .,;:?!\t\n" 로 구분된 식별자들로 이루어진 파일(FILE_NAME)
출력 :
        식별자들과 stringtable(ST)에서의 index, 존재 정보
Global 변수 :
    ST: String Table 배열
    HT: Hash Table로 ST의 index로 표현된다.
    letters: A..Z, a..z, _
    digits: 0~9
    seperators: null , . ; : ? ! \t \n \r
*****************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "witherr_input3.txt"
#define STsize 1000 //String Table 크기
#define HTsize 100 //Hash Table 크기
#define Isize 25 //입력 식별자의 최대 크기
#define isWord(x) ((((x>='a'&&(x)<='z') || ((x)>='A'&&(x)<='Z')) || (x=='_') )
#define isNum(x) ((x) >= '0' && (x) <= '9')
#define idlen 12 //identifier 최대 길이 12

    typedef struct HTentry* HTpointer;
typedef struct HTentry
{
    int index;      //ST에서의 식별자 index(head index)
    HTpointer next; //다음 식별자의 포인터
} HTentry;

//에러 분류에 도움을 주는 errorTypes
enum errorTypes
{
    noerror,
    illsp,
    illid,
    overst,
    overfl,
    noidentifier
};

typedef enum errorTypes ERRORtypes;
char separators[] = " .,;:?!\t\r\n";
HTpointer HT[HTsize];
char ST[STsize];

int nid = 0;   //현재 identifier 위치 index
int nfree = 0; //ST에서 다음으로 빈 index
int sameid = 0;//identifier의 첫번쨰 index
int flag = 0;  //0이면 중복 없음, 1이면 중복 있음
int EOFflag = 1;
int initalize_done = 0;

ERRORtypes errr;
FILE* fp; //파일 포인터
char input;
char string[Isize];
int hashcode; //ComputeHT 결과 저장 변수

void initialize() {
    fp = fopen(FILE_NAME, "r");
    input = fgetc(fp); initalize_done = 1;
}

//isSeperator 함수: char c가 seperator에 해당여부(0/1) 출력
int isSeparator(char c)
{
    for (int i = 0; i < strlen(separators); i++)
    {
        if (c == separators[i] || c == '\r')
            return 1;
    }
    return 0;
}

//isWordNum 함수: char c가 word/Num에 해당여부(0/1) 출력
int isWordNum(char c)
{
    if (isWord(c) || isNum(c)))
    return 1;
    else
        return 0;
}

// PrintHStable 함수: HashTable 결괏값 출력 - hashcode, identifier list와 전체 character 출력
void PrintHStable()
{
    printf("[[ HASH TABLE ]]\n\n");

    int i = 0;
    while (i < HTsize) {
        if (HT[i] != NULL) {
            printf("Hash code %-3d: ", i); //hashcode 출력
            HTpointer pt = HT[i];
            while (pt != NULL) {
                //그 hashcode의 identifier list 출력
                int st_index = pt->index;
                while (ST[st_index] != '\0' && st_index < STsize) printf("%c", ST[st_index++]);
                printf(" ");
                pt = pt->next;
            }
            printf("\n");
        }
        i++;
    }
    printf("\n<%d characters are used in the string table>\n", nfree); //nfree로 전체 character 출력
}

//PrintError 함수: ERRORtypes 객체 내용을 바탕으로 ERROR 정보를 출력
// error: illsp(허용되지 않는 문자 사용한 식별자 에러, SkipSeperators함수)
//        illid(숫자와 함께 시작하는 식별자 에러,SkipStartWithNumber함수)
//        overst(식별자길이idlen을 넘는 식별자 에러, get_identifier함수)
//        overfl(파일 크기로 overflow 발생, ReadIO함수)
void PrintError(ERRORtypes err)
{
    printf("***ERROR***\t\t");
    if (err == illsp)
    {
        for (int i = 0; string[i] != '\0'; i++) printf("%c", string[i]);
        printf(" is not allowed\n");
    }

    else if (err == illid)
    {
        for (int i = 0; string[i] != '\0'; i++) printf("%c", string[i]);
        printf(" starts with digit\n");
    }

    else if (err == overst)
    {
        for (int i = 0; string[i] != '\0'; i++) printf("%c", string[i]);
        printf(" is more than 12 words\n");
    }

    else if (err == overfl)
    {
        printf("\tOVERFLOW\n");
        printf("\n\n==================================================\n");
        PrintHStable();
        exit(0);
    }
}

//get_identifier 함수: identifier 단위로 접근하여 overst 에러 확인
void get_identifier()
{
    int i = 0; char temp;
    if (initalize_done == 1) { temp = input; initalize_done = 0; }
    else temp = fgetc(fp);
    while (1) {
        if (!isSeparator(temp)) break;
        temp = fgetc(fp);
    }

    for (i = 0; i < Isize; i++) {
        if (temp == EOF || isSeparator(temp))
        {
            string[i] = '\0';
            if (temp == EOF) EOFflag = 0;
            break;
        }
        else
        {
            string[i] = temp;
        }
        temp = fgetc(fp);
    }
    if (i == 0) {
        //separator 뒤에 EOF인 경우 string에 '\0'만 들어가있음
        errr = noidentifier;
    }
    if (i > idlen) {
        errr = overst;
        PrintError(errr);
    }
}

//SkipSeperators 함수: 허용하지 않은 문자 있는지 확인(illsp 에러 체크)
void SkipSeparators()
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (!isWordNum(string[i]))
        {
            errr = illsp;
            PrintError(errr);
            break;
        }
        i++;
    }
}

//SkipStartWithNumber 함수: 숫자로 시작하는지 확인(illid 에러 체크)
void SkipStartWithNumber()
{
    if (isNum(string[0]))
    {
        errr = illid;
        PrintError(errr);
    }
}

//ReadIO 함수: FILE_NAME에 해당하는 fp로 파일 읽어서 ST에 넣기(overfl 에러 체크)
void ReadID()
{
    nid = nfree;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (nfree >= STsize) //STSize overflow
        {
            errr = overfl;
            PrintError(errr);
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
    int a, b; //a: HT의 index, b: 현재 identifier의 index
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

void PrintHeading() {
    printf("==================================================\n");
    printf("컴파일러 과제 1\n");
    printf("1조 - 박기은, 이혜인, 한지수\n");
    printf("==================================================\n\n");
}

// main 함수
// FILE_NAME에 해당하는 파일 열기
// while{
//        identifer의 에러(overst, illsp, illid) 확인
//        1. ReadID: ST에 identifier 저장, overfl 확인
//        2. ComputeHS: identifier에 대한 해시 함수 결과 설정
//        3. LookupHS: 해시 함수 결과 바탕으로 HS에 접근, flag 값 설정
//        4. ADDHT: HT에 identifier 추가
// }
// Hash Table 결과 출력하기
int main()
{
    PrintHeading();
    int i;
    initialize();

    printf("------------\t\t----------\n");
    printf("Index in ST\t\tIdentifier\n");
    printf("------------\t\t----------\n");

    while (EOFflag) {
        errr = noerror;

        get_identifier(); //overst, noidentifier 확인
        SkipSeparators(); //illsp 확인
        SkipStartWithNumber(); //illid 확인

        if (errr == noerror)
        {
            ReadID(); //overfl 확인
            ST[nfree++] = '\0';
            ComputeHS(nid, nfree);
            LookupHS(nid, hashcode);

            if (!flag) {
                printf("%-11d\t\t", nid);
                i = nid;
                while (i < nfree - 1) printf("%c", ST[i++]);
                printf("...(entered)\n");
                ADDHT(hashcode);
            }
            else {
                printf("%-11d\t\t", sameid);
                i = nid;
                while (i < nfree - 1) printf("%c", ST[i++]);
                printf("…(already exists)\n");
                nfree = nid;
            }
        }

    }

    printf("\n\n==================================================\n");
    PrintHStable();
}