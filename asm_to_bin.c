#include <stdio.h>
#include <string.h>

#include "asm_to_bin.h"

// KEYDOWN down
// JMPFALSE no_down
// ADDC $0 1 /* adds to register $0, carrying into $1 (little-endian) */
// :no_down
// SPR 0 0 $0 /* inputs an unsigned byte for sprite index and two signed shorts (as words) for position; automatically culls if outside of screen */

int asm_to_bin(const char *asm_path, unsigned char start_instr[65536], unsigned char frame_instr[65536]) {

	// print every token in the asm, counting the linebreaks
	FILE *f = fopen(asm_path, "r");

	if(f == NULL) {
		fprintf(stderr, "\x1b[31m[GameKitty] Could not read instructions\n\x1b[0m");
		return 1;
	}

	char token[64];
	int ignore = 0;
	int instr_i = 0;
  
    while (fscanf(f, "%63s", token) != EOF) {

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

		// map this instruction (and its arguments, if any) to a binary

		// note:
		//   (u)i = (unsigned) immediate value
		//   (u)a = (unsigned) value-at-address (no registers for simplicity)
		//   0x00 = finish
		
		if (!strcmp(token, "SPR")) {

			// 0x01 = draw sprite with parameters index(ui8) x(i16) y(i16)

			// SPR 0 20 20
			// 0x01 0x00 0x0B 0x00 0x0B 0x00

			frame_instr[instr_i++] = 0x01;

			unsigned char index;
			short x, y;

			fscanf(f, "%hhu %hd %hd", &index, &x, &y);

			frame_instr[instr_i++] = index;
			frame_instr[instr_i++] = x & 0x00FF;
			frame_instr[instr_i++] = x & 0xFF00;
			frame_instr[instr_i++] = y & 0x00FF;
			frame_instr[instr_i++] = y & 0xFF00;

		} else {

			fprintf(stderr, "\x1b[31m[GameKitty] Encountered unexpected token: %s\n\x1b[0m", token); // TODO track line of token
			return 1;
		}
	}

	fclose(f);

	return 0;
}