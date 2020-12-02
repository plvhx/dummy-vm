#ifndef __VM_H__
#define __VM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct vm_value {
	int32_t value;
	struct vm_value *next;
} vm_value_t;

vm_value_t *vm_value_create(void);
vm_value_t *vm_value_push(vm_value_t *node, int32_t val);
int32_t vm_value_pop(vm_value_t *node);
int32_t vm_value_empty(vm_value_t *node);
void vm_value_destroy(vm_value_t *node);

void vm_repl(uint8_t *buf);

#ifdef __cplusplus
}
#endif

#endif /* __VM_H__ */
