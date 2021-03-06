#ifndef __VM_H__
#define __VM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "regs.h"
#include "value.h"

typedef struct vm_state {
  int opcode;
  struct vm_state *next;
} vm_state_t;

typedef struct vm_stack {
  vm_value_t *value;
  struct vm_stack *next;
} vm_stack_t;

typedef struct vm {
  unsigned char *buf;
  int ip;
  int is_error;
  size_t buflen;
  vm_regs_t *regs;
  vm_state_t *state;
  vm_stack_t *stack;
} vm_t;

#define VM_REGS_GET_R0_VAL(vm) REGS_GET_R0_VAL(vm->regs)
#define VM_REGS_GET_R1_VAL(vm) REGS_GET_R1_VAL(vm->regs)
#define VM_REGS_GET_R2_VAL(vm) REGS_GET_R2_VAL(vm->regs)
#define VM_REGS_GET_R3_VAL(vm) REGS_GET_R3_VAL(vm->regs)

vm_state_t *vm_state_create(void);
vm_state_t *vm_state_insert(vm_state_t *state, int opcode);
void vm_state_destroy(vm_state_t *state);

vm_stack_t *vm_stack_create(void);
vm_stack_t *vm_stack_push(vm_stack_t *stack, vm_value_t *value);
int vm_stack_empty(vm_stack_t *stack);
vm_value_t *vm_stack_pop(vm_stack_t *stack);
void vm_stack_destroy(vm_stack_t *stack);

vm_t *vm_init(char *buf, size_t len);
void vm_run(vm_t *vm);
void vm_destroy(vm_t *vm);

#ifdef __cplusplus
}
#endif

#endif /* __VM_H__ */
