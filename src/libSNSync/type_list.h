#ifndef TYPE_LIST_H
#define TYPE_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>

struct TYPES_LIST {
	char *tableName;
	char *extension;
	char *fieldName;
	struct TYPES_LIST *next;
};

typedef struct TYPES_LIST TYPES_LIST;

TYPES_LIST* initializeTypesList();
void defineTableName(char* tableName, TYPES_LIST**);
void defineExtension(char* extension, TYPES_LIST**);
void defineFieldName(char* fieldName, TYPES_LIST**);
TYPES_LIST* defineNextType(TYPES_LIST**);

#ifdef __cplusplus
}
#endif

#endif
