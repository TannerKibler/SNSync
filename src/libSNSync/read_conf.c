#include "read_conf.h"

char PATH_KEY[5] = "path\0";
char ENDPOINT_KEY[9] = "endpoint\0";
char UNAME_KEY[9] = "username\0";
char PSWD_KEY[9] = "password\0";
char FILE_KEY[11] = "file_types\0";

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
	else if (strncmp(str, FILE_KEY, 10) == 0) {
		return FILE_KEY;
	}

	return key;
}

char* substring(char *str, int stIndex, int enIndex) {
	char *retString = NULL;
	int loopIn = 0;
	if ((stIndex != 0 && stIndex == NULL) || enIndex == NULL)
		return NULL;
	if (stIndex >= enIndex)
		return NULL;
	if (str == NULL || str[stIndex] == NULL || str[enIndex] == NULL)
		return NULL;

	if ((enIndex - stIndex) > 1)
		retString = malloc((sizeof(char)*(enIndex - stIndex) + 8));
	else
		retString = malloc(32);
	while(stIndex <= enIndex && str[stIndex] != '\0') {
		retString[loopIn] = str[stIndex];
		stIndex++;
		loopIn++;
	}

	retString[loopIn] = '\0';

	return retString;
}

int check_splitter(char x, char split) {
	int split_check = 0;
	if (x == split) {
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
	sync.firstType = NULL;
	TYPES_LIST *firstType = NULL;
	TYPES_LIST *placeholderTypes = NULL;
	TYPES_LIST *currentType = NULL;
	char *buffer = NULL;
	char *str = NULL, *current_key = NULL, *tmp = NULL, *substr = NULL;
	char *value = NULL;
	int reading = 0;
	int i = 0, j = 1, x = 0, y = 0, z = 0, ln = 0;

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
				if (check_splitter(buffer[i], SPLITTER_EQUALS_SIGN) == 1) {
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
				tmp = realloc(value,(x+1) * 2);
				if (tmp == NULL) {
					printf("Massive failure.");
					return sync;
				}
				value = tmp;
				value[x] = buffer[i];
				if (buffer[i+1] != '\0' && check_end_of_line(buffer[i+1]) == 1) {
					value[x+1] = '\0';

					if (strncmp(current_key, PATH_KEY, 4) == 0) {
						sync.path = malloc(strlen(value)*2);
						strcpy(sync.path, value);
						//free(value);
					}
					else if (strncmp(current_key, ENDPOINT_KEY, 8) == 0) {
						sync.endpoint = malloc(strlen(value)*2);
						strcpy(sync.endpoint, value);
						//free(value);
					}
					else if (strncmp(current_key, UNAME_KEY, 8) == 0) {
						sync.username = malloc(strlen(value)*2);
						strcpy(sync.username, value);
						//free(value);
					}
					else if (strncmp(current_key, PSWD_KEY, 8) == 0) {
						sync.password = malloc(strlen(value)*2);
						strcpy(sync.password, value);
						//free(value);
					}
					else if (strncmp(current_key, FILE_KEY, 10) == 0) {
						if (currentType == NULL) { // FIRST TYPE NOT REALLY NULL??? CHECK THIS FIRST THING!
							//placeholderTypes = malloc((sizeof(TYPES_LIST))+8);
							placeholderTypes = initializeTypesList();
							while (value[y] != '\0' && value[y] != EOF) {
								if (check_splitter(value[y], SPLITTER_COMMA) == 1) {

									// MAKE SURE YOU TRIM THE STRING AT THE COMMA, THIS IS STILL CATCHING THE PREV EXTENSION


									// IF COMMA, we are going to start again
									if (sync.firstType == NULL) {
										sync.firstType = initializeTypesList();
										sync.firstType = placeholderTypes;

										placeholderTypes = defineNextType(&sync.firstType);
									}
									else {
										currentType = placeholderTypes;
										placeholderTypes = defineNextType(&currentType);
									}
								}
								else if (check_splitter(value[y], SPLITTER_PERIOD) == 1) {
									// IF PERIOD, we are grabbing the field name
									ln = y - z;
									substr = malloc(((sizeof(char))*((y-1)-z)) + 8);
									substr = substring(value, z, y-1);
									defineFieldName(substr, &placeholderTypes);
									z = (y+1);
								}
								else if (check_splitter(value[y], SPLITTER_COLON) == 1) {
									// IF COLON, we are grabbing the table name
									ln = y - z;
									substr = malloc(((sizeof(char))*((y-1)-z)) + 4);
									substr = substring(value, z, y-1);
									defineTableName(substr, &placeholderTypes);
									z = (y+1);
								}
								else if (x == y || (check_splitter(value[y], SPLITTER_SEMI) == 1)) {
									// IF SEMICOLON OR EOL, we are grabbing the extension
									ln = y - z;
									if (x == y) { // End of string

									// START HERE NEXT TIME, THIS NEEDS TO BE UPDATED

									
										placeholderTypes->extension = malloc(32);
										placeholderTypes->extension = substring(value, z, y);
										placeholderTypes->extension[ln+1] = '\0';	
									}
									else {
										placeholderTypes->extension = substring(value, z, y-1);
										placeholderTypes->extension[ln] = '\0';
									}

									z = (y+1);

								}
								y++;
							}
							y = 0;
						}
					}
				}
			}

			tmp = realloc(str,(x+1) * 2);
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
		free(buffer);
		free(current_key);
		//free(tmp);
		free(value);
	}
	//printf(sync.firstType->extension);
	return sync;
}
