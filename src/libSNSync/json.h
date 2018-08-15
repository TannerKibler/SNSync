#ifndef JSON_H
#define JSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct JSON_OBJECT_NODE {
	char* key;
	void* value;
	void* last;
	void* next;
	void** children;
};

typedef struct JSON_OBJECT_NODE JSON_OBJECT_NODE;

#define KEYVALUE_TERM '\"'
#define KEYVALUE_SPLIT ':'
#define NODE_END ','
#define START_OBJECT '{'
#define END_OBJECT '}'
#define START_ARRAY '['
#define END_ARRAY ']'

JSON_OBJECT_NODE* load_json_from_file(char* fileName);
int is_char_keyvalue_term(char x);
int is_char_keyvalue_split(char x);
int is_char_node_end(char x);
int is_char_object_start(char x);
int is_char_object_end(char x);
int is_char_array_start(char x);
int is_char_array_end(char x);

#ifdef __cplusplus
}
#endif

#endif
