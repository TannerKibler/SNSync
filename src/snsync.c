#include <stdio.h>
#include <stdlib.h>
#include "libSNSync/read_conf.h"
#include "libSNSync/json.h"
#include "libSNSync/http.h"
#include "libSNSync/type_list.h"

int main(int argc, char** argv) {
	struct SYNC_CONFIG sync_conf;
	sync_conf = loadSyncConfig();
	printf("Path: %s\n", sync_conf.path);
	printf("Endpoint: %s\n", sync_conf.endpoint);
	printf("User: %s\n", sync_conf.username);
	printf("Pass: %s\n", sync_conf.password);
	printf("Table: %s\n", sync_conf.firstType->tableName);
	printf("Field: %s\n", sync_conf.firstType->fieldName);
	printf("Extension: %s\n", sync_conf.firstType->extension);
	createRecord(sync_conf.endpoint, "incident\0", sync_conf.username, sync_conf.password);
	free(sync_conf.endpoint);
	free(sync_conf.username);
	free(sync_conf.password);
	free(sync_conf.path);
	//load_json_from_file("/home/arch/code/c/examples/test");

//	for (int x = 0; x < argc; x++) {
//		printf("%i: %s\n", x, argv[x]);
//		createRecord(sync_conf.endpoint, "incident");
//	}

	return 0;
}
