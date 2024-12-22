#include <stdio.h>
#include <string.h>
#include "noobutil.h"

int main(int argc, char** argv) {
	if (argc < 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0) {
		printf("			-to To Encode into a base64 string\n");
		printf("			-from To Decode from a base64 string\n");
	} else if (argc > 2 && strcmp(argv[1], "-to") == 0) {
		char* result = encode_to_base64_string(argv[2]);
		printf("%s\n", result);
		free(result);
	} else if (argc > 2 && strcmp(argv[1], "-from") == 0) {
		char* result = decode_from_base64_string(argv[2]);
		printf("%s\n", result);
		free(result);
	}

	return 0;
}
