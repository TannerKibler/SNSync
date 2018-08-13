#include <stdio.h>
#include <stdlib.h>
#include "libSNSync/read_conf.h"

int main(void) {
	struct SYNC_CONFIG sync_conf;
	sync_conf = loadSyncConfig();
	printf("Path: %s\n", sync_conf.path);
	printf("Endpoint: %s\n", sync_conf.endpoint);
	printf("User: %s\n", sync_conf.username);
	printf("Pass: %s\n", sync_conf.password);
	return 0;
}
