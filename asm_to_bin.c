#include <stdio.h>
#include <string.h>

#include "asm_to_bin.h"

int asm_to_bin(const char *asm_path, unsigned char bin[65536]) {

	// print every token in the asm, counting the linebreaks
	FILE *f = fopen(asm_path, "r");

	if(f == NULL) {
		fprintf(stderr, "\x1b[31m[GameKitty] Could not read instructions\n\x1b[0m");
		return 1;
	}

	char token[64];
	int ignore = 0;
  
    while (fscanf(f, "%63s", token) != EOF) {

		// fprintf(stderr, "\x1b[31m[GameKitty] Encountered unexpected token: %s\n\x1b[0m", ____);

		if (!strcmp(token, "/*")) {
			ignore = 1;
			continue;
		}
		
		if (!strcmp(token, "*/")) {
			ignore = 0;
			continue;
		}

		if (ignore)
			continue;
		
		printf("%s\n", token);
	}

	fclose(f); 

	return 0;
}