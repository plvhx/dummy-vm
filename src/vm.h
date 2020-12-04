#ifndef __VM_H__
#define __VM_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vm_state {
	int opcode;
	struct vm_state *next;
} vm_state_t;

typedef struct vm_stack {
	short value;
	struct vm_stack *next;
} vm_stack_t;

typedef struct vm {
	char *buf;
	unsigned int ip;
	unsigned int is_error;
	vm_state_t *state;
	vm_stack_t *stack;
} vm_t;

vm_state_t *vm_state_create(void);
vm_state_t *vm_state_insert(vm_state_t *state, int opcode);
void vm_state_destroy(vm_state_t *state);

vm_stack_t *vm_stack_create(void);
vm_stack_t *vm_stack_push(vm_stack_t *stack, short value);
int vm_stack_empty(vm_stack_t *stack);
short vm_stack_pop(vm_stack_t *stack);
void vm_stack_destroy(vm_stack_t *stack);

vm_t *vm_init(char *buf);
void vm_run(vm_t *vm);
void vm_destroy(vm_t *vm);

#ifdef __cplusplus
}
#endif

#endif /* __VM_H__ */
