#include <assert.h>
#include <stdlib.h>

#include "regs.h"

vm_regs_t *vm_regs_init(void)
{
	vm_regs_t *regs = calloc(1, sizeof(vm_regs_t));
	assert(regs != NULL);

	regs->gp = vm_gp_regs_init();
	return regs;
}

void vm_regs_destroy(vm_regs_t *regs)
{
	vm_gp_regs_destroy(regs->gp);
	free(regs);
}

vm_gp_regs_t *vm_gp_regs_init(void)
{
	vm_gp_regs_t *gp = calloc(1, sizeof(vm_gp_regs_t));
	assert(gp != NULL);

	gp->r0 = vm_value_create();
	gp->r1 = vm_value_create();
	gp->r2 = vm_value_create();
	gp->r3 = vm_value_create();
	return gp;
}

void vm_gp_regs_destroy(vm_gp_regs_t *gp)
{
	free(gp->r3);
	free(gp->r2);
	free(gp->r1);
	free(gp->r0);
	free(gp);
}
