#include <assert.h>
#include <stdlib.h>

#include "regs.h"

vm_regs_t *vm_regs_init(void)
{
	vm_regs_t *regs = calloc(1, sizeof(vm_regs_t));
	assert(regs != NULL);

	regs->gp.r0 = 0;
	regs->gp.r1 = 0;
	regs->gp.r2 = 0;
	regs->gp.r3 = 0;
	return regs;
}

void vm_regs_destroy(vm_regs_t *regs)
{
	free(regs);
}
