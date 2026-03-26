#ifndef ASM_TO_BIN_H
#define ASM_TO_BIN_H

// (I)nstruction bytes
#define I_FINISH 0x00
#define I_SPR_III 0x01
#define I_SPR_IAA 0x02

// compiles a GameKittyASM file to a binary; returns zero on success, non-zero on failure
int asm_to_bin(const char *asm_path, unsigned char start_instr[65536], unsigned char frame_instr[65536]);

#endif