/*
* A simple example of json string parsing with json-c.
*
* clang -Wall -g -I/usr/include/json-c/ -o json_parser json_parser.c -ljson-c
*/
#include <json.h>
#include <stdio.h>

int main() {
	struct json_object *jobj;

	jobj = json_object_new_object();
	json_object_object_add(jobj, "key1", json_object_new_string("value1"));
	json_object_object_add(jobj, "key2", json_object_new_string("value2"));

	//========================== get json value ==========
	struct json_object *tmp;

	json_object_object_get_ex(jobj, "key1", &tmp);  //tmp: là value

	printf(json_object_to_json_string(tmp));
	
	return 0;
}