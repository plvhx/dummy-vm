#ifndef __INSN_H__
#define __INSN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "vm.h"

typedef enum vm_insn {
	VM_INSN_MOVB_IMM8_TO_R0 = 0x90,
	VM_INSN_MOVB_IMM8_TO_R1,
	VM_INSN_MOVB_IMM8_TO_R2,
	VM_INSN_MOVB_IMM8_TO_R3,

	VM_INSN_MOVB_R0_TO_R0 = 0xa0,
	VM_INSN_MOVB_R1_TO_R0,
	VM_INSN_MOVB_R2_TO_R0,
	VM_INSN_MOVB_R3_TO_R0,

	VM_INSN_MOVB_R0_TO_R1 = 0xb0,
	VM_INSN_MOVB_R1_TO_R1,
	VM_INSN_MOVB_R2_TO_R1,
	VM_INSN_MOVB_R3_TO_R1,

	VM_INSN_MOVB_R0_TO_R2 = 0xc0,
	VM_INSN_MOVB_R1_TO_R2,
	VM_INSN_MOVB_R2_TO_R2,
	VM_INSN_MOVB_R3_TO_R2,

	VM_INSN_MOVB_R0_TO_R3 = 0xd0,
	VM_INSN_MOVB_R1_TO_R3,
	VM_INSN_MOVB_R2_TO_R3,
	VM_INSN_MOVB_R3_TO_R3,

	VM_INSN_ADDB_IMM8_IMM8_TO_R0 = 0x40,
	VM_INSN_ADDB_IMM8_IMM8_TO_R1,
	VM_INSN_ADDB_IMM8_IMM8_TO_R2,
	VM_INSN_ADDB_IMM8_IMM8_TO_R3,

	VM_INSN_SUBB_IMM8_IMM8_TO_R0,
	VM_INSN_SUBB_IMM8_IMM8_TO_R1,
	VM_INSN_SUBB_IMM8_IMM8_TO_R2,
	VM_INSN_SUBB_IMM8_IMM8_TO_R3,

	VM_INSN_MULB_IMM8_IMM8_TO_R0,
	VM_INSN_MULB_IMM8_IMM8_TO_R1,
	VM_INSN_MULB_IMM8_IMM8_TO_R2,
	VM_INSN_MULB_IMM8_IMM8_TO_R3,

	VM_INSN_DIVB_IMM8_IMM8_TO_R0,
	VM_INSN_DIVB_IMM8_IMM8_TO_R1,
	VM_INSN_DIVB_IMM8_IMM8_TO_R2,
	VM_INSN_DIVB_IMM8_IMM8_TO_R3,

	VM_INSN_PRINT_IMM8 = 0x20,
	VM_INSN_PRINT_R0,
	VM_INSN_PRINT_R1,
	VM_INSN_PRINT_R2,
	VM_INSN_PRINT_R3
} vm_insn_t;

void vm_insn_movb_imm8_to_r0(vm_t *vm);
void vm_insn_movb_imm8_to_r1(vm_t *vm);
void vm_insn_movb_imm8_to_r2(vm_t *vm);
void vm_insn_movb_imm8_to_r3(vm_t *vm);

void vm_insn_movb_r0_to_r0(vm_t *vm);
void vm_insn_movb_r1_to_r0(vm_t *vm);
void vm_insn_movb_r2_to_r0(vm_t *vm);
void vm_insn_movb_r3_to_r0(vm_t *vm);

void vm_insn_movb_r0_to_r1(vm_t *vm);
void vm_insn_movb_r1_to_r1(vm_t *vm);
void vm_insn_movb_r2_to_r1(vm_t *vm);
void vm_insn_movb_r3_to_r1(vm_t *vm);

void vm_insn_movb_r0_to_r2(vm_t *vm);
void vm_insn_movb_r1_to_r2(vm_t *vm);
void vm_insn_movb_r2_to_r2(vm_t *vm);
void vm_insn_movb_r3_to_r2(vm_t *vm);

void vm_insn_movb_r0_to_r3(vm_t *vm);
void vm_insn_movb_r1_to_r3(vm_t *vm);
void vm_insn_movb_r2_to_r3(vm_t *vm);
void vm_insn_movb_r3_to_r3(vm_t *vm);

void vm_insn_addb_imm8_imm8_to_r0(vm_t *vm);
void vm_insn_addb_imm8_imm8_to_r1(vm_t *vm);
void vm_insn_addb_imm8_imm8_to_r2(vm_t *vm);
void vm_insn_addb_imm8_imm8_to_r3(vm_t *vm);

void vm_insn_subb_imm8_imm8_to_r0(vm_t *vm);
void vm_insn_subb_imm8_imm8_to_r1(vm_t *vm);
void vm_insn_subb_imm8_imm8_to_r2(vm_t *vm);
void vm_insn_subb_imm8_imm8_to_r3(vm_t *vm);

void vm_insn_mulb_imm8_imm8_to_r0(vm_t *vm);
void vm_insn_mulb_imm8_imm8_to_r1(vm_t *vm);
void vm_insn_mulb_imm8_imm8_to_r2(vm_t *vm);
void vm_insn_mulb_imm8_imm8_to_r3(vm_t *vm);

void vm_insn_print_imm8(vm_t *vm);
void vm_insn_print_r0(vm_t *vm);
void vm_insn_print_r1(vm_t *vm);
void vm_insn_print_r2(vm_t *vm);
void vm_insn_print_r3(vm_t *vm);

void vm_insn_unknown_bytecode_handler(vm_t *vm);

#ifdef __cplusplus
}
#endif

#endif /* __INSN_H__ */
