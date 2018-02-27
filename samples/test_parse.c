﻿/*
* A simple example of json string parsing with json-c.
*
* clang -Wall -g -I/usr/include/json-c/ -o json_parser json_parser.c -ljson-c
*/
#include <json.h>
#include <stdio.h>

int main() {
	struct json_object *jobj;
	char *str = "{ \"msg-type\": [ \"0xdeadbeef\", \"irc log\" ], \
		\"msg-from\": { \"class\": \"soldier\", \"name\": \"Wixilav\" }, \
		\"msg-to\": { \"class\": \"supreme-commander\", \"name\": \"[Redacted]\" }, \
		\"msg-log\": [ \
			\"soldier: Boss there is a slight problem with the piece offering to humans\", \
			\"supreme-commander: Explain yourself soldier!\", \
			\"soldier: Well they don't seem to move anymore...\", \
			\"supreme-commander: Oh snap, I came here to see them twerk!\" \
			] \
		}";

	printf("str:\n---\n%s\n---\n\n", str);

	//String sẽ dc parg ra JsonObject
	jobj = json_tokener_parse(str);
	
	printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));

	//Phần này để giải phóng bộ nhớ cấp phát
	json_object_put(jobj); //Release memory
	return 0;
}