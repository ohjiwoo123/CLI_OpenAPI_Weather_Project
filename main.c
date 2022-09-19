#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <stdbool.h>   // bool, true, false가 정의된 헤더 파일
#include <string.h>    // strchr, memset, memcpy 함수가 선언된 헤더 파일
#include <pthread.h>
#include <json-c/json.h>

#define BUF_SIZE 1024
#define CURL_URL "curl -s -H 'Accept: application/json' --request GET"
#define API_URL "https://api.openweathermap.org/data/2.5/weather?q="
#define API_URL_BACK "&appid=89c7e8b990973c2078cdf69c21117339&units=metric"

pthread_mutex_t mutx;
int printUi();
void *threadPrintUi(void *arg);
void disConnect();
void callWeatherByLat();
void callWeatherByCity();
void getCommandList();
void error_Handling(char *buf);

int main(int argc, char *argv[])
{
	pthread_t printUiThread;
	int threadCheck;
	int status;
	pthread_mutex_init(&mutx, NULL);

	while(1)
	{
		threadCheck = pthread_create(&printUiThread,NULL,threadPrintUi,NULL);
		if(threadCheck != 0)
		{
			printf("%d\n",threadCheck);
			error_Handling("Print UI Thread create error\n");
			continue;
		}
		pthread_join(printUiThread, (void**)&status);
		printf("Thread End : %d\n",status);
	}
	return 0;
}

int printUi()
{
	int inputNum = 0;
	// system("cls");
	printf("===================================================\n");
	printf("날씨 확인 프로그램입니다.\n");
	printf("---------------------------------------------------\n");
	printf("[1] 사용 설명서\t [2] 프로그램 종료\t\n");
	printf("===================================================\n");

	// 사용자가 선택한 메뉴의 값을 반환한다.
	scanf("%d", &inputNum);
	//getchar();
	//버퍼에 남은 엔터 제거용
	while (getchar() != '\n'); //scanf_s 버퍼 비우기, 밀림 막음
	if (inputNum > 2 || inputNum < 1)
	{
		inputNum = 3; // 0~2 사이의 메뉴 값이 아니라면 defalut로 보내기
	}
	return inputNum;
}

void *threadPrintUi(void *arg)
{
	int menuNum = 0;

	pthread_mutex_lock(&mutx);
	while((menuNum = printUi()) !=0)
	{
		switch(menuNum)
		{
			case 1:
				getCommandList();
				break;
			case 2:
				disConnect();
				break;
			default:
				printf("메뉴의 보기에 있는 숫자 중에서 입력하세요.\n");
				break;
		}
	}
	pthread_mutex_unlock(&mutx);
}

void getCommandList()
{
	int inputNumber = 0;
	printf("===================================================\n");
	printf("현재 프로그램에서 제공되는 기능은 아래와 같습니다.\n");
	printf("[1] 위도,경도를 입력하고 날씨 호출하기\n");
	printf("[2] 도시 이름으로 날씨 호출하기\n");
	printf("번호를 입력하세요 : ");

	scanf("%d",&inputNumber);

	switch(inputNumber)
	{	case 1:
			callWeatherByLat();
			break;
		case 2:
			callWeatherByCity();
			break;
		default:
			printf("위에 제공된 번호 중에서 입력하세요\n");
			break;
	}
}

void disConnect()
{

}

void callWeatherByLat()
{

}

void callWeatherByCity()
{
	json_object *myJsonObj, *weatherKeyObj, *mainKeyObj;
    	json_object *dataObj, *dataValObj;

	char cityName[20];
	char curlCommand[BUF_SIZE];
	char buf[BUF_SIZE];
	char *readBuffer;
	printf("===================================================\n");
	printf("도시 이름을 입력하세요 (도시명을 잘못 입력할 시 결과출력X)\n");
	scanf("%s",cityName);
	sprintf(curlCommand,"%s '%s%s%s'",CURL_URL,API_URL,cityName,API_URL_BACK);
        //printf("%s\n",curlCommand);

	FILE *fp;
        FILE *file;
        fp = popen(curlCommand,"r");
        file = fopen("/home/jwoh/http_Project/CLI_OpenAPI_Weather_Project/src/result.json","w");

        while(fgets(buf,BUF_SIZE,fp))
        {
                //printf("%s\n",buf);
                fputs(buf,file);
        }
        pclose(fp);
        fclose(file);

	FILE *rfp;
	rfp = fopen("/home/jwoh/http_Project/CLI_OpenAPI_Weather_Project/src/result.json","r");
	
	readBuffer = malloc(1024);
	fread(readBuffer,1024,1,rfp);

	myJsonObj = json_tokener_parse(readBuffer);

	weatherKeyObj = json_object_object_get(myJsonObj, "weather");
	mainKeyObj = json_object_object_get(myJsonObj, "main");

	// 웨더 영역 파싱 
	dataObj = json_object_array_get_idx(weatherKeyObj,0);
	//printf("%s\n",json_object_get_string(dataObj));
	dataValObj = json_object_object_get(dataObj, "description");
	printf("현재 날씨는 : %s\n", json_object_get_string(dataValObj));


	// 메인 영역 파싱 
	dataValObj = json_object_object_get(mainKeyObj, "temp");
	printf("현재기온은 : %s\n", json_object_get_string(dataValObj));


	//dataObj = json_object_object_get(dataobj, "nameInfo");

	fclose(rfp);
	free(readBuffer);
}

void error_Handling(char *buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}

