#include <stdio.h>
#include "insn.h"
#include "vm.h"

#define VM_ALIGN_TO_BYTE(val)	((val) & 0xff)

static unsigned short vm_insn_read_byte(vm_t *vm)
{
	return (short)(vm->buf[++vm->ip] & 0xff);
}

static unsigned short vm_insn_read_word(vm_t *vm)
{
	unsigned short msb = (vm->buf[++vm->ip] & 0xff) << 8;
	unsigned short lsb = (vm->buf[++vm->ip] & 0xff);
	return (msb | lsb);
}

void vm_insn_movb_imm8_to_r0(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R0);
	vm->regs->gp.r0 = vm_insn_read_byte(vm);
}

void vm_insn_movb_imm8_to_r1(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R1);
	vm->regs->gp.r1 = vm_insn_read_byte(vm);
}

void vm_insn_movb_imm8_to_r2(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R2);
	vm->regs->gp.r2 = vm_insn_read_byte(vm);
}

void vm_insn_movb_imm8_to_r3(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_IMM8_TO_R3);
	vm->regs->gp.r3 = vm_insn_read_byte(vm);
}

void vm_insn_movb_r0_to_r0(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R0);
	vm->regs->gp.r0 = VM_ALIGN_TO_BYTE(vm->regs->gp.r0);
}

void vm_insn_movb_r1_to_r0(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R0);
	vm->regs->gp.r0 = VM_ALIGN_TO_BYTE(vm->regs->gp.r1);
}

void vm_insn_movb_r2_to_r0(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R0);
	vm->regs->gp.r0 = VM_ALIGN_TO_BYTE(vm->regs->gp.r2);
}

void vm_insn_movb_r3_to_r0(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R0);
	vm->regs->gp.r0 = VM_ALIGN_TO_BYTE(vm->regs->gp.r3);
}

void vm_insn_movb_r0_to_r1(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R1);
	vm->regs->gp.r1 = VM_ALIGN_TO_BYTE(vm->regs->gp.r0);
}

void vm_insn_movb_r1_to_r1(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R1);
	vm->regs->gp.r1 = VM_ALIGN_TO_BYTE(vm->regs->gp.r1);
}

void vm_insn_movb_r2_to_r1(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R1);
	vm->regs->gp.r1 = VM_ALIGN_TO_BYTE(vm->regs->gp.r2);
}

void vm_insn_movb_r3_to_r1(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R1);
	vm->regs->gp.r1 = VM_ALIGN_TO_BYTE(vm->regs->gp.r3);
}

void vm_insn_movb_r0_to_r2(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R2);
	vm->regs->gp.r2 = VM_ALIGN_TO_BYTE(vm->regs->gp.r0);
}

void vm_insn_movb_r1_to_r2(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R2);
	vm->regs->gp.r2 = VM_ALIGN_TO_BYTE(vm->regs->gp.r1);
}

void vm_insn_movb_r2_to_r2(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R2);
	vm->regs->gp.r2 = VM_ALIGN_TO_BYTE(vm->regs->gp.r2);
}

void vm_insn_movb_r3_to_r2(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R2);
	vm->regs->gp.r2 = VM_ALIGN_TO_BYTE(vm->regs->gp.r3);
}

void vm_insn_movb_r0_to_r3(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R0_TO_R3);
	vm->regs->gp.r3 = VM_ALIGN_TO_BYTE(vm->regs->gp.r0);
}

void vm_insn_movb_r1_to_r3(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R1_TO_R3);
	vm->regs->gp.r3 = VM_ALIGN_TO_BYTE(vm->regs->gp.r1);
}

void vm_insn_movb_r2_to_r3(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R2_TO_R3);
	vm->regs->gp.r3 = VM_ALIGN_TO_BYTE(vm->regs->gp.r2);
}

void vm_insn_movb_r3_to_r3(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MOVB_R3_TO_R3);
	vm->regs->gp.r3 = VM_ALIGN_TO_BYTE(vm->regs->gp.r3);
}

void vm_insn_store_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_STORE);
	vm->stack = vm_stack_push(vm->stack, vm_insn_read_byte(vm));
}

void vm_insn_store16_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_STORE_16);
	vm->stack = vm_stack_push(vm->stack, vm_insn_read_word(vm));
}

void vm_insn_add_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_ADD_OP);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #1 must be exist.\n");
		vm->is_error = 1;
	}

	short op2 = vm_stack_pop(vm->stack);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #2 must be exist.\n");
		vm->is_error = 1;
	}

	short op1 = vm_stack_pop(vm->stack);

	// add these two integer and push back to the stack.
	vm_stack_push(vm->stack, op1 + op2);
}

void vm_insn_sub_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_SUB_OP);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #1 must be exist.\n");
		vm->is_error = 1;
	}

	short op2 = vm_stack_pop(vm->stack);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #2 must be exist.\n");
		vm->is_error = 1;
	}

	short op1 = vm_stack_pop(vm->stack);

	// subtract these two integer and push back to the stack.
	vm_stack_push(vm->stack, op1 - op2);
}

void vm_insn_mul_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_MUL_OP);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #1 must be exist.\n");
		vm->is_error = 1;
	}

	short op2 = vm_stack_pop(vm->stack);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #2 must be exist.\n");
		vm->is_error = 1;
	}

	short op1 = vm_stack_pop(vm->stack);

	// multiply these two integer and push back to the stack.
	vm_stack_push(vm->stack, op1 * op2);
}

void vm_insn_div_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_DIV_OP);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #1 must be exist.\n");
		vm->is_error = 1;
	}

	short op2 = vm_stack_pop(vm->stack);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Operand #2 must be exist.\n");
	}

	short op1 = vm_stack_pop(vm->stack);

	if (!op2) {
		fprintf(stderr, "Division by zero.\n");
		vm->is_error = 1;
	}

	// divide these two integer and push back to the stack.
	vm_stack_push(vm->stack, op1 / op2);
}

void vm_insn_display_op(vm_t *vm)
{
	vm->state = vm_state_insert(vm->state, VM_INSN_DISPLAY);

	if (vm_stack_empty(vm->stack)) {
		fprintf(stderr, "Stack empty.\n");
		vm->is_error = 1;
	}

	fprintf(stdout, "%d\n", vm_stack_pop(vm->stack));
}

void vm_insn_unknown_bytecode_handler(vm_t *vm)
{
	fprintf(stderr, "Unknown bytecode (%d).\n", vm->buf[vm->ip]);
	vm->is_error = 1;
}
