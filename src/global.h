#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ast.h"

typedef struct vm_compiler_global {
	vm_ast_t *ast;
} vm_compiler_global_t;

static vm_compiler_global_t compiler_global = {
	.ast = NULL
};

#define VM_CG(field)	((compiler_global).field)

#ifdef __cplusplus
}
#endif

#endif /* __GLOBAL_H__ */
