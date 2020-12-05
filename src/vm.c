#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "insn.h"
#include "vm.h"

vm_state_t *vm_state_create(void)
{
	vm_state_t *ret = calloc(1, sizeof(vm_state_t));
	assert(ret != NULL);

	ret->opcode = -1;
	ret->next = NULL;
	return ret;
}

vm_state_t *vm_state_insert(vm_state_t *state, int opcode)
{
	if (state == NULL) {
		return NULL;
	}

	vm_state_t *tmp = (vm_state_t *)state;
	vm_state_t *new;

	while (tmp->next != NULL) {
		tmp = tmp->next;
	}

	new = vm_state_create();
	new->opcode = opcode;
	new->next = tmp->next;
	tmp->next = new;
	return state;
}

void vm_state_destroy(vm_state_t *state)
{
	if (state == NULL) {
		return;
	}

	vm_state_destroy(state->next);
	free(state);
}

vm_stack_t *vm_stack_create(void)
{
	vm_stack_t *ret = calloc(1, sizeof(vm_stack_t));
	assert(ret != NULL);

	ret->value = -1;
	ret->next = NULL;
	return ret;
}

vm_stack_t *vm_stack_push(vm_stack_t *stack, unsigned short value)
{
	if (stack == NULL) {
		return NULL;
	}

	vm_stack_t *new = vm_stack_create();
	new->next = stack->next;
	new->value = value;
	stack->next = new;
	return stack;
}

int vm_stack_empty(vm_stack_t *stack)
{
	return stack->next == NULL ? 1 : 0;
}

unsigned short vm_stack_pop(vm_stack_t *stack)
{
	vm_stack_t *tmp = stack->next;
	short rval = tmp->value;

	stack->next = stack->next->next == NULL ? NULL : stack->next->next;
	free(tmp);

	return rval;
}

void vm_stack_destroy(vm_stack_t *stack)
{
	free(stack);
}

vm_t *vm_init(char *buf)
{
	vm_t *vm = calloc(1, sizeof(vm_t));
	assert(vm != NULL);

	vm->buf = strdup(buf);
	vm->ip = -1;
	vm->is_error = 0;
	vm->regs = vm_regs_init();
	vm->state = vm_state_create();
	vm->stack = vm_stack_create();
	return vm;
}

void vm_run(vm_t *vm)
{
	while (vm->buf[++vm->ip] != '\0' && !vm->is_error) {
		switch (vm->buf[vm->ip]) {
			// move imm8 to general-purpose register.
			case VM_INSN_MOVB_IMM8_TO_R0:
				vm_insn_movb_imm8_to_r0(vm);
				break;
			case VM_INSN_MOVB_IMM8_TO_R1:
				vm_insn_movb_imm8_to_r1(vm);
				break;
			case VM_INSN_MOVB_IMM8_TO_R2:
				vm_insn_movb_imm8_to_r2(vm);
				break;
			case VM_INSN_MOVB_IMM8_TO_R3:
				vm_insn_movb_imm8_to_r3(vm);
				break;
			// move general-purpose register value as
			// byte value to 'r0' general-purpose register.
			case VM_INSN_MOVB_R0_TO_R0:
				vm_insn_movb_r0_to_r0(vm);
				break;
			case VM_INSN_MOVB_R1_TO_R0:
				vm_insn_movb_r1_to_r0(vm);
				break;
			case VM_INSN_MOVB_R2_TO_R0:
				vm_insn_movb_r2_to_r0(vm);
				break;
			case VM_INSN_MOVB_R3_TO_R0:
				vm_insn_movb_r3_to_r0(vm);
				break;
			// move general-purpose register value as
			// byte value to 'r1' general-purpose register.
			case VM_INSN_MOVB_R0_TO_R1:
				vm_insn_movb_r0_to_r1(vm);
				break;
			case VM_INSN_MOVB_R1_TO_R1:
				vm_insn_movb_r1_to_r1(vm);
				break;
			case VM_INSN_MOVB_R2_TO_R1:
				vm_insn_movb_r2_to_r1(vm);
				break;
			case VM_INSN_MOVB_R3_TO_R1:
				vm_insn_movb_r3_to_r1(vm);
				break;
			// move general-purpose register value as
			// byte value to 'r2' general-purpose register.
			case VM_INSN_MOVB_R0_TO_R2:
				vm_insn_movb_r0_to_r2(vm);
				break;
			case VM_INSN_MOVB_R1_TO_R2:
				vm_insn_movb_r1_to_r2(vm);
				break;
			case VM_INSN_MOVB_R2_TO_R2:
				vm_insn_movb_r2_to_r2(vm);
				break;
			case VM_INSN_MOVB_R3_TO_R2:
				vm_insn_movb_r3_to_r2(vm);
				break;
			// move general-purpose register value as
			// byte value to 'r3' general-purpose register.
			case VM_INSN_MOVB_R0_TO_R3:
				vm_insn_movb_r0_to_r3(vm);
				break;
			case VM_INSN_MOVB_R1_TO_R3:
				vm_insn_movb_r1_to_r3(vm);
				break;
			case VM_INSN_MOVB_R2_TO_R3:
				vm_insn_movb_r2_to_r3(vm);
				break;
			case VM_INSN_MOVB_R3_TO_R3:
				vm_insn_movb_r3_to_r3(vm);
				break;
			case VM_INSN_STORE:
				vm_insn_store_op(vm);
				break;
			case VM_INSN_STORE_16:
				vm_insn_store16_op(vm);
				break;
			case VM_INSN_ADD_OP:
				vm_insn_add_op(vm);
				break;
			case VM_INSN_SUB_OP:
				vm_insn_sub_op(vm);
				break;
			case VM_INSN_MUL_OP:
				vm_insn_mul_op(vm);
				break;
			case VM_INSN_DIV_OP:
				vm_insn_div_op(vm);
				break;
			case VM_INSN_DISPLAY:
				vm_insn_display_op(vm);
				break;
			default:
				vm_insn_unknown_bytecode_handler(vm);
				break;
		}
	}
}

void vm_destroy(vm_t *vm)
{
	vm_stack_destroy(vm->stack);
	vm_state_destroy(vm->state);

	vm->ip = -1;

	free(vm->buf);
	free(vm);
}
