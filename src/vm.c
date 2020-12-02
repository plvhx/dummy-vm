#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "insn.h"
#include "vm.h"

vm_value_t *vm_value_create(void)
{
	vm_value_t *ret = calloc(1, sizeof(vm_value_t));
	assert(ret != NULL);
	return ret;
}

void vm_value_destroy(vm_value_t *node)
{
	free(node);
	return;
}

vm_value_t *vm_value_push(vm_value_t *node, int32_t val)
{
	if (node == NULL) {
		return NULL;
	}

	vm_value_t *current = node;

	vm_value_t *new = vm_value_create();
	new->value = val;
	new->next = node->next;
	node->next = new;

	return node;
}

int32_t vm_value_pop(vm_value_t *node)
{
	vm_value_t *tmp = node->next;
	int32_t ret = tmp->value;

	node->next = tmp->next;
	vm_value_destroy(tmp);

	return ret;
}

int32_t vm_value_empty(vm_value_t *node)
{
	return node->next == NULL;
}

static size_t vm_insn_store(vm_value_t **stack, const char *buf, size_t offset)
{
	char *tmp = calloc(64, sizeof(char));
	int i;

	assert(tmp != NULL);

	for (i = 0; buf[offset + i] >= 0x30 && buf[offset + i] <= 0x39; i++) {
		tmp[i] = buf[offset + i];
	}

	vm_value_push(*stack, atoi(tmp));
	free(tmp);

	return i + 1;
}

void vm_repl(uint8_t *buf)
{
	vm_value_t *stack = vm_value_create();
	size_t off = 0, op_idx = 0;
	int32_t operand[2] = {0, 0};
	int32_t ret = 0;

	while (buf[off] != '\0') {
		switch (buf[off]) {
			case VM_INSN_STORE:
				off += vm_insn_store(&stack, buf, off + 1);
				break;
			case VM_INSN_LOAD:
				operand[op_idx++] = vm_value_pop(stack);
				off++;
				break;
			case VM_INSN_ADD_OP:
				ret = operand[0] + operand[1];
				{ off++; op_idx = 0; }
				break;
			case VM_INSN_SUB_OP:
				ret = operand[0] - operand[1];
				{ off++; op_idx = 0; }
				break;
			case VM_INSN_MUL_OP:
				ret = operand[0] * operand[1];
				{ off++; op_idx = 0; }
				break;
			case VM_INSN_DIV_OP:
				if (!operand[1]) {
					fprintf(stderr, "Division by zero.\n");
					goto done;
				}

				ret = operand[0] / operand[1];
				{ off++; op_idx = 0; }
				break;
			case VM_INSN_DISPLAY:
				printf("%f\n", (double)ret);
				off++;
				break;
			default:
				fprintf(stderr, "(0x%02x) is an invalid bytecode.\n", buf[off]);
				goto done;
		}
	}

done:
	vm_value_destroy(stack);
	return;
}
