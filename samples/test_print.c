/*
* Various outputs for flag of json_object_to_json_string_ext().
*
* clang -Wall -I/usr/include/json-c/ -o json_print json_print.c -ljson-c
*/
#include <json.h>
#include <stdio.h>

int main() {
	struct json_object *jobj;
	const char *question = "Mum, clouds hide alien spaceships don't they ?";
	const char *answer = "Of course not! (\"sigh\")";
	int i;

	// các định dạng để convert JsonObject ra String
	struct {
		int flag;
		const char *flag_str;
	} json_flags[] = {
		{ JSON_C_TO_STRING_PLAIN, "JSON_C_TO_STRING_PLAIN" },
	{ JSON_C_TO_STRING_SPACED, "JSON_C_TO_STRING_SPACED" },
	{ JSON_C_TO_STRING_PRETTY, "JSON_C_TO_STRING_PRETTY" },
	{ JSON_C_TO_STRING_NOZERO, "JSON_C_TO_STRING_NOZERO" },
	{ JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY, "JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY" },
	{ -1, NULL }
	}; // Create an anonymous struct, instanciate an array and fill it

	printf("Using printf(): \"%s\", \"%s\"\n\n", question, answer);
	printf("Using json_object_to_json_string_ext():\n");

	/*
	* key = "question", value = jsonObject
	* key = "answer" , value = jsonObject
	*/
	jobj = json_object_new_object();
	json_object_object_add(jobj, "question", json_object_new_string(question));
	json_object_object_add(jobj, "answer", json_object_new_string(answer));

	// các định dạng để convert JsonObject ra String
	for (i = 0; json_flags[i].flag_str != NULL; i++) {
		printf("\nFlag %s:\n---\n", json_flags[i].flag_str);
		// các định dạng để convert JsonObject ra String
		printf("%s\n---\n", json_object_to_json_string_ext(jobj, json_flags[i].flag));
	}

	//Phần này để giải phóng bộ nhớ cấp phát
	json_object_put(jobj); //Release memory

	return 0;
}