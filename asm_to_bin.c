#include <stdio.h>
#include <string.h>

#include "asm_to_bin.h"

int asm_to_bin(const char *asm_path, unsigned char start_instr[65536], unsigned char frame_instr[65536]) {

	// print every token in the asm, counting the linebreaks
	FILE *f = fopen(asm_path, "r");

	if(f == NULL) {
		fprintf(stderr, "\x1b[31m[GameKitty] Could not read instructions\n\x1b[0m");
		return 1;
	}

	char token[64];
	int comment_layer = 0;
	int instr_i = 0;
  
    while (fscanf(f, "%63s", token) != EOF) {

		if (!strcmp(token, "/*")) {
			comment_layer++;
			continue;
		}
		
		if (!strcmp(token, "*/")) {
			comment_layer--;
			continue;
		}

		if (comment_layer)
			continue;

		// map this instruction (and its arguments, if any) to a binary
		// legend:
		//   (u)i = (unsigned) immediate value
		//   (u)a = (unsigned) value-at-address (addresses are always 16 bits, but the data fetched at that address may vary)
		
		if (!strcmp(token, "SPR")) {

			// draws a sprite with given parameters (automatically culls if outside of screen)

			// SPR 0  0  0 => I_SPR_III index(ui8) x(i16) y(i16)
			// SPR 0 $0 $0 => I_SPR_IAA index(ui8) x(a16) y(a16) // TODO

			frame_instr[instr_i++] = I_SPR_III;

			unsigned char index;
			short x, y;

			fscanf(f, "%hhu %hd %hd", &index, &x, &y);

			frame_instr[instr_i++] = index;
			frame_instr[instr_i++] = x & 0x00FF;
			frame_instr[instr_i++] = x & 0xFF00;
			frame_instr[instr_i++] = y & 0x00FF;
			frame_instr[instr_i++] = y & 0xFF00;

			// TODO implement
			// KEYDOWN down => I_DOWN (puts state of _ into the status register's zero flag)
			// JMPFALSE 0 (jumps if status register's zero flag is 0)
			// ADDC $0 1 /* adds to register $0, carrying into $1 (little-endian) */
			// :0
			// SPR 0 $0 $0

		} else {

			fprintf(stderr, "\x1b[31m[GameKitty] Encountered unexpected token: %s\n\x1b[0m", token); // TODO track line of token
			return 1;
		}
	}

	fclose(f);

	return 0;
}