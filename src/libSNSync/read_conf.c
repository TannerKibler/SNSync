#include "read_conf.h"

char *PATH_KEY = "path\0";
char *ENDPOINT_KEY = "endpoint\0";
char *UNAME_KEY = "username\0";
char *PSWD_KEY = "password\0";

char* seek_keys(char *str) {
	char *key = 0;

	if (strncmp(str, PATH_KEY, 4) == 0) {
		//	key = (char*)malloc(sizeof(char) * 4);
		//	key = PATH_KEY;
		return PATH_KEY;
	}

	if (strncmp(str, ENDPOINT_KEY, 8) == 0) {
		//key = (char*)malloc(sizeof(char) * 8);
		//key = ENDPOINT_KEY;
		return ENDPOINT_KEY;
	}

	if (strncmp(str, UNAME_KEY, 8) == 0) {
		//		key = (char*)malloc(sizeof(char) * 8);
		//		key = UNAME_KEY;
		return UNAME_KEY;
	}

	if (strncmp(str, PSWD_KEY, 8) == 0) {
		//		key = (char*)malloc(sizeof(char) * 8);
		//		key = PSWD_KEY;
		return PSWD_KEY;
	}

	return key;
}

SYNC_CONFIG loadSyncConfig() {
	SYNC_CONFIG sync;
	char *buffer = 0;
	char *str = 0, *path_value = 0, *endpoint_value = 0, *uname_value = 0, *pswd_value = 0, *current_key = 0;
	int reading = 0;
	int i = 0, j = 1, x = 0;
	buffer = read_file("/home/arch/code/c/SNSyncUtil/SNSyncConfig.txt");

	if (buffer) {
		//str = (char*)malloc(sizeof(char));
		//path_value = (char*)malloc(sizeof(char));
		//endpoint_value = (char*)malloc(sizeof(char));
		//uname_value = (char*)malloc(sizeof(char));
		//pswd_value = (char*)malloc(sizeof(char));
		current_key = (char*)malloc(sizeof(char)*50);

		while (buffer[i] != '\0') {
			
			if (reading == 0 && buffer[i] == SPLITTER_EQUALS_SIGN && (i <= 1 || buffer[i-1] != '\\')) {
				current_key = seek_keys(str);
				if (current_key) {
					reading = 1;
					x = 0;
					j = 1;
					i++;
					str = NULL;
					continue;		
				}
			}
			else if (reading == 1 && buffer[i] != '\n') {
				if (strncmp(current_key, PATH_KEY, 4) == 0) {
					//reading path
					path_value = (char*)realloc(path_value, j * sizeof(char));
					path_value[x] = buffer[i];
				}
				else if (strncmp(current_key, ENDPOINT_KEY, 8) == 0) {
					//reading endpoint
					endpoint_value = (char*)realloc(endpoint_value, j * sizeof(char));
					endpoint_value[x] = buffer[i];
				}
				else if (strncmp(current_key, UNAME_KEY, 8) == 0) {
					//reading endpoint
					uname_value = (char*)realloc(uname_value, j * sizeof(char));
					uname_value[x] = buffer[i];
				}
				else if (strncmp(current_key, PSWD_KEY, 8) == 0) {
					//reading endpoint
					printf("%c", buffer[i]);
					pswd_value = (char*)realloc(pswd_value, j * sizeof(char));
					pswd_value[x] = buffer[i];
				}
			}
			else {
				if (buffer[i] == '\n') {
					reading = 0;
					i++;
					x = 0;
					j = 1;
					continue;
				}
			}
			str = (char*)realloc(str, j * sizeof(char));
			str[x] = buffer[i];
			x++;
			i++;
			j++;
		}
		free(str);
		//TODO: What the hell is wrong with this pointer?
		//free(current_key);

		path_value = (char*)realloc(path_value,sizeof(char));
		path_value[strlen(path_value)] = '\0';
		endpoint_value = (char*)realloc(endpoint_value,sizeof(char));
		endpoint_value[strlen(endpoint_value)] = '\0';
		uname_value = (char*)realloc(uname_value,sizeof(char));
		uname_value[strlen(uname_value)] = '\0';
		pswd_value = (char*)realloc(pswd_value,sizeof(char));
		pswd_value[strlen(pswd_value)] = '\0';

		sync.path = path_value;
		sync.endpoint = endpoint_value;
		sync.username = uname_value;
		sync.password = pswd_value;
	}
	return sync;
}
