#ifndef HTTP_H
#define HTTP_H

//#include <stdio.h>
//#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

int createRecord(char* instance, char* table, char* user, char* pass);
char* myconcat(char* x, char* y);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


#ifdef __cplusplus
}
#endif

#endif
