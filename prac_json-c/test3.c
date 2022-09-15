#include <stdio.h>
#include <string.h>

#include <json-c/json.h>

#define FILE_NAME_LEN (64)

#define PRINT_KEY_VALUE(type,obj) \
	switch(type){ \
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

void parseJsonObject1(json_object * pInput)
{
	json_object * pJsonObject = NULL;
	int type = 0;

	pJsonObject = json_object_object_get(pInput,"name");
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

	pJsonObject = json_object_object_get(pInput,"hobby");
	if( json_object_get_type(pJsonObject) != json_type_array) return;

	for( i = 0 ; i < json_object_array_length(pJsonObject) ; i++)
	{
		json_object * temp = json_object_array_get_idx(pJsonObject,i);
		type = json_object_get_type(temp);
		printf("[ex4]");
		PRINT_KEY_VALUE(type,temp);
	}
}

int main(int argc, char * argv[])
{
	json_object * pJsonObject = NULL;
	char szFileName[FILE_NAME_LEN] = "result.json";
	int ret = 0;

	if( argc == 2 )
	{
		printf("%s\n",argv[1]);
		strncpy(szFileName,argv[1],FILE_NAME_LEN);
	}

	pJsonObject = json_object_from_file(szFileName);
	if ( pJsonObject == NULL )
	{
		printf("Reading file object is failed.");
		return -1;
	}

	parseJsonObject1(pJsonObject);
	parseJsonObject2(pJsonObject);
	parseJsonObject3(pJsonObject);

	parseJsonArray1(pJsonObject);

	json_object_put(pJsonObject);
	pJsonObject = NULL;

	return 0;
}
