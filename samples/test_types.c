
/*
* Exploring the types of json-c.
*
* clang -Wall -I/usr/include/json-c/ -o json_types json_types.c -ljson-c
*/
#include <json.h>
#include <stdio.h>

int main() {
	struct json_object *array, *object, *tmp, *secu_code, *doublObject;
	char *val_type_str, *str;
	int val_type, i;

	array = json_object_new_array();
	object = json_object_new_object();

	//================ Fill the array => create an array Object =========
	tmp = json_object_new_int(12345);
	json_object_array_add(array, tmp);
	tmp = json_object_new_int(44444); //1 = TRUE
	json_object_array_add(array, tmp);

	//==================================== Fill the object ===============
	tmp = json_object_new_string("We have been made!");
	json_object_object_add(object, "key_string", tmp);

	tmp = json_object_new_double(12.2345);
	json_object_object_add(object, "key_double", tmp);

	tmp = json_object_new_boolean(0); //1 = TRUE, 0 = FALSE
	json_object_object_add(object, "key_boolean", tmp);

	json_object_object_add(object, "key_array", array);

	array = tmp = NULL; // "Nothing in the sleeves"
	str = NULL;

	//=======================================================================
	// key and val don't exist outside of this bloc
	// duyệt toàn bộ JsonObject để check type of các Object trong đó
	json_object_object_foreach(object, key, val) {
		printf("key: \"%s\", type of val: ", key);
		val_type = json_object_get_type(val);
		
		switch (val_type) {
		case json_type_null:
			val_type_str = "val is NULL";
			break;

		case json_type_boolean:
			val_type_str = "val is a boolean";
			break;

		case json_type_double:
			val_type_str = "val is a double";
			break;

		case json_type_int:
			val_type_str = "val is an integer";
			break;

		case json_type_string:
			val_type_str = "val is a string";
			str = (char *)json_object_get_string(val);
			break;

		case json_type_object:
			val_type_str = "val is an object";
			break;

		case json_type_array:
			val_type_str = "val is an array";
			break;
		}

		printf("%s", val_type_str);

		if (str)
			printf("\t->\t\"%s\"", str);

		printf("\n");
		str = NULL;
	}

	printf("\nDetails of the security code:\n");
	// Get the json_object associated to the "security-code" key in secu_code
	json_object_object_get_ex(object, "key_array", &secu_code);

	// For each case of the secu_code array
	for (i = 0; i < json_object_array_length(secu_code); i++) {
		// Set in tmp the json_object of the secu_code array at index i
		tmp = json_object_array_get_idx(secu_code, i);
		printf("key_array[%d] = %s\n", i, json_object_to_json_string(tmp));
	}

	printf("\nJson in plain text: \n");
	printf("---\n%s\n---\n", json_object_to_json_string(object));

	//Phần này để giải phóng bộ nhớ cấp phát
	//các JsonObject trong Json phải tự đc giải phóng riêng
	//trong function này ko có recursive loop để giải phóng các object ở trong object
	//Muốn giải phóng tất cả phải viết 1 hàm riêng
	json_object_put(object); //Release memory
	json_object_put(array); //Release memory
	json_object_put(doublObject); //Release memory
	json_object_put(secu_code); //Release memory
	json_object_put(tmp); //Release memory


	//Nên dùng vòng lặp đệ qui với object để giải phóng 1 loạt thì hay hơn

	return 0;
}