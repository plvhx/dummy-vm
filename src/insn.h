#ifndef __INSN_H__
#define __INSN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "vm.h"

typedef enum vm_insn {
	VM_INSN_STORE = 0x01,
	VM_INSN_STORE_16,

	VM_INSN_ADD_OP = 0x10,
	VM_INSN_SUB_OP,
	VM_INSN_MUL_OP,
	VM_INSN_DIV_OP,

	VM_INSN_DISPLAY = 0x20,
} vm_insn_t;

void vm_insn_store_op(vm_t *vm);
void vm_insn_store16_op(vm_t *vm);
void vm_insn_add_op(vm_t *vm);
void vm_insn_sub_op(vm_t *vm);
void vm_insn_mul_op(vm_t *vm);
void vm_insn_div_op(vm_t *vm);
void vm_insn_display_op(vm_t *vm);
void vm_insn_unknown_bytecode_handler(vm_t *vm);

#ifdef __cplusplus
}
#endif

#endif /* __INSN_H__ */
