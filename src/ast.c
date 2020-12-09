#define _DEFAULT_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "insn.h"

static vm_ast_t *vm_ast_alloc(size_t size)
{
	vm_ast_t *ret = malloc(size);
	assert(ret != NULL);
	memset(ret, 0, size);
	return ret;
}

static vm_ast_t *vm_ast_realloc(vm_ast_t *ast, size_t old_size, size_t new_size)
{
	assert(new_size > old_size);
	vm_ast_t *ret = realloc(ast, new_size);
	assert(ret != NULL);
	memset(ret + old_size, 0, new_size - old_size);
	return ret;
}

static size_t vm_ast_calculate_child(size_t num_child)
{
	return (sizeof(vm_ast_t) - sizeof(vm_ast_t *)) + (sizeof(vm_ast_t *) * num_child);
}

static vm_ast_t *vm_ast_create_from_va_list(unsigned short kind_type, const void *ast_value, va_list args)
{
	vm_ast_t *node = vm_ast_create(kind_type, ast_value);
	vm_ast_t *child;

	while ((child = (vm_ast_t *)va_arg(args, vm_ast_t *)) != NULL) {
		node = vm_ast_add_child(node, child);
	}

	return node;
}

vm_ast_t *vm_ast_create(unsigned short kind_type, const void *ast_value)
{
	vm_ast_t *ret = vm_ast_alloc(vm_ast_calculate_child(4));

	ret->kind_type = kind_type;
	ret->num_childs = 0;
	ret->num_childs_alloc_size = 4;

	switch (ret->kind_type) {
		case VM_AST_REGISTER:
			ret->regs.name = (unsigned char *)ast_value;
			break;
		case VM_AST_MNEMONIC:
			ret->mnemonic.name = (unsigned char *)ast_value;
			break;
		case VM_AST_INTEGER_VALUE:
			ret->number.val = (unsigned char *)ast_value;
			break;
	}

	return ret;
}

vm_ast_t *vm_ast_create_multi_ex(unsigned short kind_type, const void *ast_value, ...)
{
	va_list ap;
	vm_ast_t *ret;

	va_start(ap, ast_value);
	ret = vm_ast_create_from_va_list(kind_type, ast_value, ap);
	va_end(ap);

	return ret;
}

vm_ast_t *vm_ast_add_child(vm_ast_t *ast, vm_ast_t *child)
{
	if (ast->num_childs >= ast->num_childs_alloc_size) {
		ast = vm_ast_realloc(
			ast,
			vm_ast_calculate_child(ast->num_childs_alloc_size),
			vm_ast_calculate_child(ast->num_childs_alloc_size + 4)
		);

		ast->num_childs_alloc_size += 4;
	}

	ast->childs[ast->num_childs++] = child;
	return ast;
}

static void vm_ast_process_instruction_line(vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode))
{
	assert(ast->childs[0]->kind_type == VM_AST_MNEMONIC && ast->childs[1]->kind_type == VM_AST_REGISTER);

	// process 'movb' imm8 to general-purpose regs
	if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
		!strcasecmp((char *)ast->childs[1]->regs.name, "r0") &&
		ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE) {
		visitor(file, VM_INSN_MOVB_IMM8_TO_R0);
		visitor(file, ast->childs[2]->number.val[0] == '-' ? 0xff : 0xfa);
		visitor(file, atoi((char *)ast->childs[2]->number.val + 1));
	} else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
		!strcasecmp((char *)ast->childs[1]->regs.name, "r1") &&
		ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE) {
		visitor(file, VM_INSN_MOVB_IMM8_TO_R1);
		visitor(file, ast->childs[2]->number.val[0] == '-' ? 0xff : 0xfa);
		visitor(file, atoi((char *)ast->childs[2]->number.val + 1));
	} else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
		!strcasecmp((char *)ast->childs[1]->regs.name, "r2") &&
		ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE) {
		visitor(file, VM_INSN_MOVB_IMM8_TO_R2);
		visitor(file, ast->childs[2]->number.val[0] == '-' ? 0xff : 0xfa);
		visitor(file, atoi((char *)ast->childs[2]->number.val + 1));
	} else if (!strcasecmp((char *)ast->childs[0]->mnemonic.name, "movb") &&
		!strcasecmp((char *)ast->childs[1]->regs.name, "r3") &&
		ast->childs[2]->kind_type == VM_AST_INTEGER_VALUE) {
		visitor(file, VM_INSN_MOVB_IMM8_TO_R3);
		visitor(file, ast->childs[2]->number.val[0] == '-' ? 0xff : 0xfa);
		visitor(file, atoi((char *)ast->childs[2]->number.val + 1));
	}
}

void vm_ast_traverse(vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode))
{
	if (ast == NULL) {
		return;
	}

	int i;

	if (ast->kind_type == VM_AST_INSTRUCTION_LINE) {
		vm_ast_process_instruction_line(ast, file, visitor);
	}

	for (i = 0; i < ast->num_childs; i++) {
		vm_ast_traverse(ast->childs[i], file, visitor);
	}
}
