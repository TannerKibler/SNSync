#ifndef READ_CONF_H
#define READ_CONF_H

//#include <stdio.h>
//#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "file.h"

struct SYNC_CONFIG {
	char *path;
	char *endpoint;
	char *username;
	char *password;
};

typedef struct SYNC_CONFIG SYNC_CONFIG;

#define SPLITTER_EQUALS_SIGN '='
#define SPLITTER_COLON ':'

SYNC_CONFIG loadSyncConfig();
char* seek_keys(char *str);

#ifdef __cplusplus
}
#endif

#endif
