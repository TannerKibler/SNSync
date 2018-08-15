#include <stdio.h>
#include <stdlib.h>
#include "libSNSync/read_conf.h"
#include "libSNSync/json.h"

int main(int argc, char** argv) {
	struct SYNC_CONFIG sync_conf;
	sync_conf = loadSyncConfig();
	load_json_from_file("/home/arch/code/c/examples/test");
	printf("Path: %s\n", sync_conf.path);
	printf("Endpoint: %s\n", sync_conf.endpoint);
	printf("User: %s\n", sync_conf.username);
	//printf("Pass: %s\n", sync_conf.password);

	for (int x = 0; x < argc; x++) {
		printf("%i: %s\n", x, argv[x]);
	}

	return 0;
}
