#ifndef __AST_H__
#define __AST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

typedef enum vm_kind {
	VM_AST_ROOT,
	VM_AST_MNEMONIC,
	VM_AST_REGISTER,
	VM_AST_INTEGER_VALUE,
	VM_AST_INSTRUCTION_LINE
} vm_kind_t;

typedef union vm_register {
	unsigned char *name;
} vm_register_t;

typedef union vm_mnemonic {
	unsigned char *name;
} vm_mnemonic_t;

typedef union vm_number {
	unsigned char *val;
} vm_number_t;

typedef struct vm_ast {
	unsigned short kind_type;
	vm_register_t regs;
	vm_mnemonic_t mnemonic;
	vm_number_t number;
	size_t num_childs;
	size_t num_childs_alloc_size;
	struct vm_ast *childs[1];
} vm_ast_t;

#define VM_EXPAND_VA_(x)	x
#define VM_EXPAND_VA(x)		VM_EXPAND_VA_(x)

#define VM_AST_VARIADIC_CALL_SPEC_(func, suffix, ...) \
	func ## suffix

#define VM_AST_VARIADIC_CALL_SPEC(func, ...) \
	VM_EXPAND_VA(VM_AST_VARIADIC_CALL_SPEC_(func,)(__VA_ARGS__))

// call spec with fixed args
#define VM_AST_CALL_SPEC_0(func) \
	VM_AST_VARIADIC_CALL_SPEC(func)

#define VM_AST_CALL_SPEC_1(func, a) \
	VM_AST_VARIADIC_CALL_SPEC(func, a)

#define VM_AST_CALL_SPEC_2(func, a, b) \
	VM_AST_VARIADIC_CALL_SPEC(func, a, b)

#define VM_AST_CALL_SPEC_3(func, a, b, c) \
	VM_AST_VARIADIC_CALL_SPEC(func, a, b, c)

#define VM_AST_CALL_SPEC_4(func, a, b, c, d) \
	VM_AST_VARIADIC_CALL_SPEC(func, a, b, c, d)

#define VM_AST_CALL_SPEC_5(func, a, b, c, d, e) \
	VM_AST_VARIADIC_CALL_SPEC(func, a, b, c, d, e)

#define vm_ast_create_single_ex_call(a, b) \
	VM_AST_CALL_SPEC_2(vm_ast_create, a, b)

#define vm_ast_create_multi_ex_call(a, b, ...) \
	VM_AST_VARIADIC_CALL_SPEC(vm_ast_create_multi_ex, a, b, __VA_ARGS__)

vm_ast_t *vm_ast_create(unsigned short kind_type, const void *ast_value);
vm_ast_t *vm_ast_create_multi_ex(unsigned short kind_type, const void *ast_value, ...);
vm_ast_t *vm_ast_add_child(vm_ast_t *ast, vm_ast_t *child);
void vm_ast_traverse(vm_ast_t *ast, FILE *file, void (*visitor)(FILE *file, int opcode));

#ifdef __cplusplus
}
#endif

#endif /* __AST_H__ */
