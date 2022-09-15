#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define BUF_SIZE 1024
#define SECRET_KEY "89c7e8b990973c2078cdf69c21117339"
#define CURL_URL "curl -s -H 'Accept: application/json' --request GET"
#define API_URL "https://api.openweathermap.org/data/2.5/weather?q="
#define API_URL_BACK "&appid=89c7e8b990973c2078cdf69c21117339"
#define TOKEN_COUNT 30    // 토큰의 최대 개수

// 토큰 종류 열거형
typedef enum _TOKEN_TYPE {
    TOKEN_STRING,    // 문자열 토큰
    TOKEN_NUMBER,    // 숫자 토큰
} TOKEN_TYPE;

// 토큰 구조체
typedef struct _TOKEN {
    TOKEN_TYPE type;    // 토큰 종류
    union {             // 두 종류 중 한 종류만 저장할 것이므로 공용체로 만듦
        char *string;       // 문자열 포인터
        double number;      // 실수형 숫자
    };
    bool isArray;       // 현재 토큰이 배열인지 표시
} TOKEN;

// JSON 구조체
typedef struct _JSON {
    TOKEN tokens[TOKEN_COUNT]; // 토큰 배열
} JSON;

int tokenIndex = 0;    // 토큰 인덱스

char *readFile(char *filename, int *readSize)    // 파일을 읽어서 내용을 반환하는 함수
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
        return NULL;

    int size;
    char *buffer;

    // 파일 크기 구하기
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
    buffer = malloc(size + 1);
    memset(buffer, 0, size + 1);

    // 파일 내용 읽기
    if (fread(buffer, size, 1, fp) < 1)
    {
        *readSize = 0;
        free(buffer);
        fclose(fp);
        return NULL;
    }

    // 파일 크기를 넘겨줌
    *readSize = size;

    fclose(fp);    // 파일 포인터 닫기

    return buffer;
}

void parseJSON(char *doc, int size, JSON *json)    // JSON 파싱 함수
{
    int pos = 0;           // 문자 검색 위치를 저장하는 변수

    if (doc[pos] != '{')   // 문서의 시작이 {인지 검사
        return;

    pos++;    // 다음 문자로

    while (pos < size)       // 문서 크기만큼 반복
    {
        switch (doc[pos])    // 문자의 종류에 따라 분기
        {
        	case '"':            // 문자가 "이면 문자열
        	{
            		char *begin = doc + pos + 1;
            		char *end = strchr(begin, '"');
            		if (end == NULL)    // "가 없으면 잘못된 문법이므로 
                		break;          // 반복을 종료

            		int stringLength = end - begin;    // 문자열의 실제 길이는 끝 위치 - 시작 위치
            		json->tokens[tokenIndex].type = TOKEN_STRING;
            		json->tokens[tokenIndex].string = malloc(stringLength + 1);
            		memset(json->tokens[tokenIndex].string, 0, stringLength + 1);
            		memcpy(json->tokens[tokenIndex].string, begin, stringLength);
    			tokenIndex++; // 토큰 인덱스 증가
           		pos = pos + stringLength + 1;    // 현재 위치 + 문자열 길이 + "(+ 1)
        	}
        	break;
        }
        pos++; // 다음 문자로
    }
}

void freeJSON(JSON *json)    // JSON 해제 함수
{
    for (int i = 0; i < TOKEN_COUNT; i++)            // 토큰 개수만큼 반복
    {
        if (json->tokens[i].type == TOKEN_STRING)    // 토큰 종류가 문자열이면
            free(json->tokens[i].string);            // 동적 메모리 해제
    }
}


int main(void)
{
	char cityName[BUF_SIZE];
	char curl_Cmd[BUF_SIZE];
	char buf[BUF_SIZE];

	memset(cityName,0,sizeof(cityName));
	memset(curl_Cmd,0,sizeof(curl_Cmd));
	memset(buf,0,sizeof(buf));

	// 도시이름 입력받기 
	scanf("%s",cityName);
	sprintf(curl_Cmd,"%s '%s%s%s'",CURL_URL,API_URL,cityName,API_URL_BACK);
	printf("%s\n",curl_Cmd);

	FILE *fp;
	FILE *file;
	fp = popen(curl_Cmd,"r");
	file = fopen("result.json","w");
	//if (fp = NULL)
	//{
	//	return;
	//}
	while(fgets(buf,BUF_SIZE,fp))
	{
		printf("%s",buf);
		fputs(buf,file);
	}
	pclose(fp);
	fclose(file);

	int size;
	char *doc = readFile("result.json",&size);
	if (doc==NULL)
	{
		return -1;
	}
	JSON json = {0,};

	parseJSON(doc,size,&json);

	for(int i=0; i<tokenIndex;i++)
	{
		printf("문자 : %s\n",json.tokens[i].string);
		//printf("숫자 : %f\n",json.tokens[i].number);
	}

	//printf("\nTitle: %s\n", json.tokens[1].string);       // 토큰에 저장된 문자열 출력(Title)
    	//printf("Genre: %s\n", json.tokens[2].string);       // 토큰에 저장된 문자열 출력(Genre)
    	//printf("Genre: %s\n", json.tokens[3].string);       // 토큰에 저장된 문자열 출력(Genre)
    	//printf("Genre: %s\n", json.tokens[4].string);       // 토큰에 저장된 문자열 출력(Genre)
    	//printf("Director: %s\n", json.tokens[5].string);    // 토큰에 저장된 문자열 출력(Director)

	freeJSON(&json);
	free(doc);

	return 0;
}


