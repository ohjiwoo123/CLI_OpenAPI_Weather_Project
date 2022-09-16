#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <json-c/json.h>
#define BUF_SIZE 1024
#define SECRET_KEY "89c7e8b990973c2078cdf69c21117339"
#define CURL_URL "curl -s -H 'Accept: application/json' --request GET"
#define API_URL "https://api.openweathermap.org/data/2.5/weather?q="
#define API_URL_BACK "&appid=89c7e8b990973c2078cdf69c21117339"
#define TOKEN_COUNT 30    // 토큰의 최대 개수
#define PRINT_KEY_VALUE(type,obj)\
	switch(type){\
		case json_type_null:\
			printf("Type is null\n");\
			break;\
		case json_type_boolean:\
			printf("%d\n",json_object_get_boolean(obj));\
			break;\
		case json_type_double:\
			printf("%f\n",json_object_get_double(obj));\
			break;\
		case json_type_int:\
			printf("%d\n",json_object_get_int(obj));\
			break;\
		case json_type_object:\
			printf("%ld\n",json_object_get_int64(obj));\
			break;\
		case json_type_array:\
			printf("%s\n",json_object_get_string(obj));\
			break;\
		case json_type_string:\
			printf("%s\n",json_object_get_string(obj));\
			break;\
	}

void parseJsonObject1(json_object *pInput)
{
	json_object * pJsonObject = NULL;
	int type = 0;

	pJsonObject = json_object_object_get(pInput,"weather");
	type = json_object_get_type(pJsonObject);
	printf("[ex1]");
	PRINT_KEY_VALUE(type,pJsonObject);
}

void parseJsonObject2(json_object * pInput)
{
	json_object * pJsonObject = NULL;
	int type = 0;

	json_object_object_foreach(pInput, key_name, value_obj)
	{
		printf("[ex2] %s\n",key_name);
		type = json_object_get_type(value_obj);
		PRINT_KEY_VALUE(type,value_obj);
	}
}

void parseJsonObject3(json_object * pInput)
{
	json_object * temp = NULL;
	char * name = NULL;
	struct json_object_iterator iter;
	struct json_object_iterator itEnd;
	int type = 0;

	iter  = json_object_iter_begin(pInput);
	itEnd = json_object_iter_end(pInput);

	while(!json_object_iter_equal(&iter, &itEnd))
	{
		name = json_object_iter_peek_name(&iter);
		temp = json_object_iter_peek_value(&iter);
		type = json_object_get_type(temp);
		printf("[ex3] %s\n",name);
		PRINT_KEY_VALUE(type,temp);
		json_object_iter_next(&iter);
	}
}

void parseJsonArray1(json_object * pInput)
{
	json_object * pJsonObject = NULL;
	int type = 0;
	int i = 0;

	pJsonObject = json_object_object_get(pInput,"weather");
	if( json_object_get_type(pJsonObject) != json_type_array)
	{
		printf("notarrayflag\n");
		return;
	}
	printf("%d\n",json_object_array_length(pJsonObject));
	for( i = 0 ; i < json_object_array_length(pJsonObject) ; i++)
	{
		json_object * temp = json_object_array_get_idx(pJsonObject,i);
		type = json_object_get_type(temp);
		printf("[ex4]");
		PRINT_KEY_VALUE(type,temp);
	}
}

int main(void)
{
	enum json_type type;
	char cityName[BUF_SIZE];
	char curl_Cmd[BUF_SIZE];
	char buf[BUF_SIZE];
	char *buffer;
	int size;
	int count;

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
	file = fopen("/home/jwoh/http_Project/CLI_OpenAPI_Weather_Project/src/result.json","w");

	while(fgets(buf,BUF_SIZE,fp))
	{
		printf("check 33\n");
		printf("%s",buf);
		fputs(buf,file);
	}
	pclose(fp);
	fclose(file);

	printf("check 44\n");

	FILE *rfp;
	rfp = fopen("/home/jwoh/http_Project/CLI_OpenAPI_Weather_Project/src/result.json","r");
	fseek(rfp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
    	size = ftell(rfp);          // 파일 포인터의 현재 위치를 얻음

    	buffer = malloc(size + 1);    // 파일 크기 + 1바이트(문자열 마지막의 NULL)만큼 동적 메모리 할당
   	memset(buffer, 0, size + 1);  // 파일 크기 + 1바이트만큼 메모리를 0으로 초기화
	fseek(rfp, 0, SEEK_SET);                // 파일 포인터를 파일의 처음으로 이동시킴
	count = fread(buffer, size, 1, rfp);    // hello.txt에서 파일 크기만큼 값을 읽음	
	json_object *jobj = json_tokener_parse(buffer);
	fclose(rfp);
	free(buffer);

	//parseJsonObject1(pJsonObject);
	//parseJsonObject2(pJsonObject);
	//parseJsonObject3(pJsonObject);
	//parseJsonArray1(pJsonObject);

	json_object_object_foreach(jobj,key,val)
	{
		type = json_object_get_type(val);
		 switch (type)
			{
			case json_type_null:
				printf("json_type_null\n");
				break;
			case json_type_boolean:
				printf("json_type_boolean\n");
				break;
			case json_type_double:
				printf("json_type_double\n");
				break;
			case json_type_int:
				printf("json_type_int\n");
				break;
			case json_type_object:
				printf("json_type_object\n");
				break;
			case json_type_array:
				printf("json_type_array\n");
	 			break;
	 		case json_type_string:
				printf("json_type_string\n");
				break;
			}
	}
	json_object_put(jobj);
	jobj = NULL;
	return 0;
}



