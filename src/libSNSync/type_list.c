#include "type_list.h"

TYPES_LIST* initializeTypesList() {
	TYPES_LIST *newType = NULL;
	newType = malloc((sizeof(TYPES_LIST)) + 8);
	if (newType == NULL) {
		// Implement error functionality
		return NULL;
	}

	return newType;
}

void defineTableName(char* tableName, TYPES_LIST** type) {
	(*type)->tableName = malloc((sizeof(char)) * (strlen(tableName)) + 8);
	if ((*type)->tableName == NULL) {
		// Implement Error functionality
		return;
	}

	(*type)->tableName = tableName;
}

void defineExtension(char* extension, TYPES_LIST** type) {
	(*type)->extension = malloc((sizeof(char)) * (strlen(extension)) + 8);
	if ((*type)->extension == NULL) {
		// Implement Error functionality
		return;
	}

	(*type)->extension = extension;
}

void defineFieldName(char* fieldName, TYPES_LIST** type) {
	(*type)->fieldName = malloc((sizeof(char)) * (strlen(fieldName)) + 8);
	if ((*type)->fieldName == NULL) {
		// Implement Error functionality
		return;
	}

	(*type)->fieldName = fieldName;
}

TYPES_LIST* defineNextType(TYPES_LIST** type) {
	TYPES_LIST* nextType = NULL;
	nextType = initializeTypesList();
	if (nextType == NULL) {
		// Implement Error functionality
		return NULL;
	}

	(*type)->next = nextType;
	
	return nextType;
}
