#include "json.h"

int is_char_keyvalue_term(char x) {
	if (x == KEYVALUE_TERM) {
		return 1;
	}
	else {
		return 0;
	}
}

int is_char_keyvalue_split(char x) {
	if (x == KEYVALUE_SPLIT) {
		return 1;
	}
	else {
		return 0;
	}

}

int is_char_node_end(char x) {
	if (x == NODE_END) {
		return 1;
	}
	else {
		return 0;
	}
}
int is_char_object_start(char x) {
	if (x == START_OBJECT) {
		return 1;
	}
	else {
		return 0;
	}
}
int is_char_object_end(char x) {
	if (x == END_OBJECT) {
		return 1;
	}
	else {
		return 0;
	}
}
int is_char_array_start(char x) {
	if (x == START_ARRAY) {
		return 1;
	}
	else {
		return 0;
	}
}
int is_char_array_end(char x) {
	if (x == END_ARRAY) {
		return 1;
	}
	else {
		return 0;
	}
}

JSON_OBJECT_NODE* load_json_from_file(char* fileName) {
	char *buffer = 0;
	char *str = strdup(""), *tmpBuff = NULL, *tmp = NULL;
	int i = 0, lastIndex = 0, reading = 0, reading_value = 0, ignore_special = 0, x = 0;
	JSON_OBJECT_NODE *first = NULL;
	JSON_OBJECT_NODE *curr_node = NULL;

	buffer = read_file(fileName);
	if(buffer) {
		str = malloc(10);
		while (buffer[i] != '\0' && buffer[i] != EOF) {
			if (is_char_keyvalue_term(buffer[i]) == 1) {

			/*************************************************************************************************************
			**	TODO: Start here first thing. Value not being set correctly. Trouble casting char* to void*.      *******
			*************************************************************************************************************/

				if (reading_value == 1) {
					if (curr_node->value == NULL) {
						tmp = malloc((i-lastIndex)*10);
						if (tmp == NULL) {
							printf("Massive failure");
							return first;
						}
						for (; lastIndex < i; lastIndex++,x++) {
							tmp[x] = buffer[lastIndex];
							printf("%c", buffer[lastIndex]);
						}
						tmp[x+1] = '\0';
						curr_node->value = malloc(x);
						printf("STRING VALUE: %s\n", tmp);
						curr_node->value = (char*)tmp;
						//strcpy(curr_node->value, tmp);
						free(tmp);
						printf("%s\n", (char*)curr_node->value);
					}
				}
				else {
					if(reading == 1) {
						tmp = malloc((i-lastIndex)*10);
						if (tmp == NULL) {
							printf("Massive failure");
							return first;
						}
						if (first == NULL) {
							first = malloc(sizeof(JSON_OBJECT_NODE) * 10);
							for (; lastIndex < i; lastIndex++,x++) {
								tmp[x] = buffer[lastIndex];
							}
							tmp[x+1] = '\0';
							first->key = malloc(x);
							strcpy(first->key, tmp);
							free(tmp);
							printf("%s\n", first->key);
						}
						else if (curr_node != NULL) {
							for (; lastIndex < i; lastIndex++,x++) {
								tmp[x] = buffer[lastIndex];
							}
							tmp[x+1] = '\0';
							curr_node->key = malloc(x);
							strcpy(curr_node->key, tmp);
							free(tmp);
							printf("%s", curr_node->key);
						}
						reading = 0;
					}
					else {
						lastIndex = i+1;
						x = 0;
						reading = 1;
						if (reading_value == 1) {
							ignore_special = 1;
						}
					}
				}
			}
			else if (is_char_keyvalue_split(buffer[i]) == 1) { // hit a value split, we can now start watching value
				reading_value = 1;
			}
			else if (is_char_array_start(buffer[i]) == 1 && ignore_special == 0) { // If reading a value, don't watch arrays or objects
				if (is_char_object_start(buffer[i+1]) == 0) { // Starting an Array

				}
				else { // Starting another level of JSON.
					reading_value = 0;
					if (curr_node == NULL) {
						curr_node = malloc(sizeof(JSON_OBJECT_NODE) * 10);
						curr_node->value = NULL;
						first->children = malloc(sizeof(JSON_OBJECT_NODE) * 10);
						first->children[0] = curr_node;
					}
				}
			}

			tmpBuff = realloc(str,(i+1) * 10);
			if (tmpBuff == NULL) {
				printf("Massive failure.");
			}
			str = tmpBuff;
			str[i] = buffer[i];
			//printf("%c", buffer[i]);
			i++;
		}
	}
	return first;
}
