#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv)
{
	FILE *fp;
	char buffer[1024];
	char *buf;

	struct json_object *parsed_json;
	struct json_object *name;
	struct json_object *age;
	struct json_object *friends;
	struct json_object *friend;

	size_t n_friends;
	size_t i;
	buf = malloc(1024);
	//memset(*buf,0,1024);

	fp = fopen("test.json","r");
	fread(buf,1024,1,fp);
	fclose(fp);
	printf("check1\n");

	parsed_json = json_tokener_parse(buf);
	json_object_object_get_ex(parsed_json,"name",&name);
	json_object_object_get_ex(parsed_json,"age",&age);
	json_object_object_get_ex(parsed_json,"friends",&friends);
	printf("check2\n");


	printf("Name : %s\n", json_object_get_string(name));
	printf("Age : %d\n", json_object_get_int(age));
	printf("check3\n");

	n_friends = json_object_array_length(friends);
	printf("Found %lu friends\n", n_friends);
	
	for(int i=0; i<n_friends;i++)
	{
		friend = json_object_array_get_idx(friends,i);
		printf("%lu. %s\n",i+1, json_object_get_string(friend));
	}
	free(buf);
	return 0;
}
Y
