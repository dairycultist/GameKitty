#ifndef ASM_TO_BIN_H
#define ASM_TO_BIN_H

// compiles a GameKittyASM file to a binary; returns zero on success, non-zero on failure
int asm_to_bin(const char *asm_path, unsigned char start_instr[65536], unsigned char frame_instr[65536]);

#endif