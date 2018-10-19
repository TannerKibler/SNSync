#ifndef READ_CONF_H
#define READ_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "file.h"
#include "type_list.h"

struct SYNC_CONFIG {
	char *path;
	char *endpoint;
	char *username;
	char *password;
	struct TYPES_LIST *firstType;

};

typedef struct SYNC_CONFIG SYNC_CONFIG;
typedef struct TYPES_LIST TYPES_LIST;

#define SPLITTER_EQUALS_SIGN '='
#define SPLITTER_COLON ':'
#define SPLITTER_COMMA ','
#define SPLITTER_SEMI ';'
#define SPLITTER_PERIOD '.'

SYNC_CONFIG loadSyncConfig();
char* seek_keys(char *str);
char* substring(char *str, int stIndex, int enIndex);
int check_end_of_line(char);
int check_splitter(char x, char split);

#ifdef __cplusplus
}
#endif

#endif
