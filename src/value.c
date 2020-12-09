#include <assert.h>
#include <stdlib.h>

#include "value.h"

vm_value_t *vm_value_create(void)
{
	vm_value_t *ret = calloc(1, sizeof(vm_value_t));
	assert(ret != NULL);

	ret->val = 0;
	return ret;
}

void vm_value_destroy(vm_value_t *value)
{
	free(value);
}
