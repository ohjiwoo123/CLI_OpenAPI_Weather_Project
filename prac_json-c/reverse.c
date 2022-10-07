#include <stdio.h>
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <stdbool.h>   // bool, true, false가 정의된 헤더 파일
#include <string.h>    // strchr, memset, memcpy 함수가 선언된 헤더 파일
#include <pthread.h>
#include <json-c/json.h>

void parsingJson(json_object *obj);
void parsingArray(json_object *obj);

int main()
{
	// Total Object
	json_object *totalObj = json_object_new_object();

	// Classify by Key
	json_object *coordObj = json_object_new_object();
	json_object *weatherObj = json_object_new_object();
	json_object *baseObj = json_object_new_object();
	json_object *mainKeyObj = json_object_new_object();
	json_object *visibilityObj = json_object_new_object();
	json_object *windObj = json_object_new_object();
	json_object *rainObj = json_object_new_object();
	json_object *cloudsObj = json_object_new_object();
	json_object *dtObj = json_object_new_object();
	json_object *sysObj = json_object_new_object();
	json_object *idObj = json_object_new_object();
	json_object *nameObj = json_object_new_object();
	json_object *codObj = json_object_new_object();

	// object inside object
	json_object *mainValObj = json_object_new_object();
	json_object *weatherValObj = json_object_new_object();

	// Value
	json_object *lonValueObj = json_object_new_string("126.9778");
	json_object *latValueObj = json_object_new_string("37.5683");
	json_object *w_idValueObj = json_object_new_string("500");
	json_object *w_mainValueObj = json_object_new_string("Rain");
	json_object *w_desValueObj = json_object_new_string("light rain");
	json_object *w_iconValueObj = json_object_new_string("100d");
	json_object *baseValueObj = json_object_new_string("stations");
	json_object *m_tempValueObj = json_object_new_string("19.34");
	json_object *m_feels_likeValueObj = json_object_new_string("19.29");
	json_object *m_temp_minValueObj = json_object_new_string("18.69");
	json_object *m_temp_maxValueObj = json_object_new_string("19.76");
	json_object *m_pressureValueObj = json_object_new_string("1013");
	json_object *m_humidityValueObj = json_object_new_string("75");
	json_object *visibilityValueObj = json_object_new_string("10000");
	json_object *w_speedValueObj = json_object_new_string("3.6");
	json_object *w_degValueObj = json_object_new_string("300");
	json_object *rainValueObj = json_object_new_string("0.4");
	json_object *cloudsValueObj = json_object_new_string("40");
	json_object *dtValueObj = json_object_new_string("1664855855");
	json_object *sys_typeValueObj = json_object_new_string("1");
	json_object *sys_idValueObj = json_object_new_string("8105");
	json_object *sys_countryValueObj = json_object_new_string("KR");
	json_object *sys_sunriseValueObj = json_object_new_string("1664832574");
	json_object *sys_sunsetValueObj = json_object_new_string("1664874729");
	json_object *timezoneValueObj = json_object_new_string("32400");
	json_object *idValueObj = json_object_new_string("1835848");
	json_object *nameValueObj = json_object_new_string("seoul");
	json_object *codValueObj = json_object_new_string("200");

	// Array
	json_object *weatherArray = json_object_new_array();
	json_object *totalArray = json_object_new_array();

	json_object_object_add(mainValObj,"temp", m_tempValueObj);
	json_object_object_add(mainValObj,"feels_like", m_feels_likeValueObj);
	json_object_object_add(mainValObj,"temp_min", m_temp_minValueObj);
	json_object_object_add(mainValObj,"temp_max", m_temp_maxValueObj);
	json_object_object_add(mainValObj,"pressure", m_pressureValueObj);
	json_object_object_add(mainValObj,"humidity", m_humidityValueObj);

	json_object_object_add(mainKeyObj,"main", mainValObj);
	printf("The json object created: %s\n",json_object_to_json_string(mainValObj));
	printf("The json object created: %s\n",json_object_to_json_string(mainKeyObj));


	json_object_object_add(weatherValObj,"id", w_idValueObj);
	json_object_object_add(weatherValObj,"main", w_mainValueObj);
	json_object_object_add(weatherValObj,"description", w_desValueObj);
	json_object_object_add(weatherValObj,"icon", w_iconValueObj);
	json_object_array_put_idx(weatherArray,0,weatherValObj);
	json_object_object_add(weatherObj,"weather", weatherArray);

	printf("The json object created: %s\n",json_object_to_json_string(weatherValObj));
	printf("The json object created: %s\n",json_object_to_json_string(weatherObj));

	json_object_object_add(mainKeyObj,"weather",weatherArray);
	printf("The json object created: %s\n",json_object_to_json_string(mainKeyObj));

	json_object_array_put_idx(totalArray,0,mainKeyObj);
	printf("The json object created: %s\n",json_object_to_json_string(totalArray));

	json_object_object_add(totalObj,"SuperParent",totalArray);
	printf("The json object created: %s\n",json_object_to_json_string(totalObj));

	parsingJson(totalObj);

	// free == put func
	return 0;
}

void parsingJson(json_object *obj)
{
   json_object_object_foreach(obj, key, val)
   {
      switch (json_object_get_type(val))
         {
          case json_type_array:
             printf("\n%s  \n\n", key);
             parsingArray(val);
             break;

          case json_type_object:
             printf("\n%s  \n\n", key);
             parsingJson(val);
             break;

          default:
             printf("%s: %s\n", key, json_object_get_string(val));
         }
   }
}

void parsingArray(json_object *obj)
{
   int temp_n = json_object_array_length(obj);
   for (int i = 0; i < temp_n; i++)
      parsingJson(json_object_array_get_idx(obj, i));
}
