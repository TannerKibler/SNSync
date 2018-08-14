#include "read_conf.h"

char PATH_KEY[5] = "path\0";
char ENDPOINT_KEY[9] = "endpoint\0";
char UNAME_KEY[9] = "username\0";
char PSWD_KEY[9] = "password\0";

char* seek_keys(char *str) {
	char *key = 0;

	if (str == NULL) {
		return key;
	}

	if (strncmp(str, PATH_KEY, 4) == 0) {
		return PATH_KEY;
	}
	else if (strncmp(str, ENDPOINT_KEY, 8) == 0) {
		return ENDPOINT_KEY;
	}
	else if (strncmp(str, UNAME_KEY, 8) == 0) {
		return UNAME_KEY;
	}
	else if (strncmp(str, PSWD_KEY, 8) == 0) {
		return PSWD_KEY;
	}

	return key;
}

int check_splitter(char x) {
	int split_check = 0;
	if (x == SPLITTER_EQUALS_SIGN) {
		split_check = 1;
	}
	return split_check;
}

int check_end_of_line(char x) {
	int eol_check = 0;
	if (x == '\n') {
		eol_check = 1;
	}
	return eol_check;
}

SYNC_CONFIG loadSyncConfig() {
	SYNC_CONFIG sync;
	char *buffer = 0;
	char *str = strdup(""), *current_key = NULL, *tmp = NULL;
	char *value = strdup("");
	int reading = 0;
	int i = 0, j = 1, x = 0;

	buffer = read_file("/home/arch/code/c/SNSyncConfig.txt");
	if (buffer) {
		str = malloc(10);
		value = malloc(10);
		while (buffer[i] != '\0' && buffer[i] != EOF) {
			if (check_end_of_line(buffer[i]) == 1) {
				current_key = NULL;
				reading = 0;
				i++;
				x = 0;
				j = 1;
				continue;
			}
			if (reading == 0) {
				if (check_splitter(buffer[i]) == 1) {
					current_key = seek_keys(str);
					if (current_key) {
						current_key[x+1] = '\0';
						reading = 1;
						x = 0;
						j = 1;
						i++;
						continue;		
					}
				}
			}
			else {
				tmp = realloc(value,(x+1) * 10);
				if (tmp == NULL) {
					printf("Massive failure.");
					return sync;
				}
				value = tmp;
				value[x] = buffer[i];
				if (buffer[i+1] != '\0' && check_end_of_line(buffer[i+1]) == 1) {
					value[x+1] = '\0';

					if (strncmp(current_key, PATH_KEY, 4) == 0) {
						sync.path = malloc((x+1) * 10);
						strcpy(sync.path, value);
						free(value);
					}
					else if (strncmp(current_key, ENDPOINT_KEY, 8) == 0) {
						sync.endpoint = malloc((x+1) * 10);
						strcpy(sync.endpoint, value);
						free(value);
					}
					else if (strncmp(current_key, UNAME_KEY, 8) == 0) {
						sync.username = malloc((x+1) * 10);
						strcpy(sync.username, value);
						free(value);
					}
					else if (strncmp(current_key, PSWD_KEY, 8) == 0) {
						sync.password = malloc((x+1) * 10);
						strcpy(sync.password, value);
						free(value);
					}
				}
			}

			tmp = realloc(str,(x+1) * 10);
			if (tmp == NULL) {
				printf("Massive failure.");
				return sync;
			}
			str = tmp;
			str[x] = buffer[i];
			x++;
			i++;
			j++;
		}
		free(str);
	}
	return sync;
}
