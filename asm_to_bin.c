#include <stdio.h>
#include <string.h>

#include "asm_to_bin.h"

int asm_to_bin(const char *asm_path, unsigned char start_instr[65536], unsigned char frame_instr[65536]) {

	// // print every token in the asm, counting the linebreaks
	// FILE *f = fopen(asm_path, "r");

	// if(f == NULL) {
	// 	fprintf(stderr, "\x1b[31m[GameKitty] Could not read instructions\n\x1b[0m");
	// 	return 1;
	// }

	// char token[64];
	// int ignore = 0;
  
    // while (fscanf(f, "%63s", token) != EOF) {

	// 	// fprintf(stderr, "\x1b[31m[GameKitty] Encountered unexpected token: %s\n\x1b[0m", ____);

	// 	if (!strcmp(token, "/*")) {
	// 		ignore = 1;
	// 		continue;
	// 	}
		
	// 	if (!strcmp(token, "*/")) {
	// 		ignore = 0;
	// 		continue;
	// 	}

	// 	if (ignore)
	// 		continue;
		
	// 	// KEYDOWN down
	// 	// JMPFALSE no_down
	// 	// ADDC $0 1 /* adds to register $0, carrying into $1 (little-endian) */
	// 	// :no_down
	// 	// SPR 0 0 $0 /* inputs an unsigned byte for sprite index and two signed shorts (as words) for position; automatically culls if outside of screen */

		
	// 	printf("%s\n", token);
	// }

	// fclose(f);

	// (u)i = (unsigned) immediate value, (u)a = (unsigned) value-at-address (no registers for simplicity)

	frame_instr[0] = 0x01; // draw sprite: index (ui8) x (i16) y(i16)
	frame_instr[1] = 0x00;
	frame_instr[2] = 0x0A;
	frame_instr[3] = 0x00;
	frame_instr[4] = 0x0A;
	frame_instr[5] = 0x00;

	// 0x00 / finish

	return 0;
}