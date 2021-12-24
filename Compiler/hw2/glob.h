/* glob.h - Hash table 구성에 필요한 global 변수들 설정
* programmer - 박기은, 이혜인, 한지수
* date - 27/04/2021
*/

#pragma once
#define STsize 1000

int line;
char ST[STsize];
int nid = 0;   //현재 identifier 위치 index
int nfree = 0; //ST에서 다음으로 빈 index
int sameid = 0;//identifier의 첫번쨰 index
int flag = 0;  //0이면 중복 없음, 1이면 중복 있음
int errcnt;