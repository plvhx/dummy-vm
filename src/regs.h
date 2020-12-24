#ifndef __REGS_H__
#define __REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"
#include "value.h"

typedef struct vm_gp_regs {
  vm_value_t *r0;
  vm_value_t *r1;
  vm_value_t *r2;
  vm_value_t *r3;
} vm_gp_regs_t;

typedef struct vm_regs {
  vm_gp_regs_t *gp;
} vm_regs_t;

#define REGS_GET_R0_VAL(regs)                                                  \
  (!regs->gp->r0->is_negative ? (regs)->gp->r0->val                            \
                              : VM_NEGATE_BYTE((regs)->gp->r0->val))

#define REGS_GET_R1_VAL(regs)                                                  \
  (!regs->gp->r1->is_negative ? (regs)->gp->r1->val                            \
                              : VM_NEGATE_BYTE((regs)->gp->r1->val))

#define REGS_GET_R2_VAL(regs)                                                  \
  (!regs->gp->r2->is_negative ? (regs)->gp->r2->val                            \
                              : VM_NEGATE_BYTE((regs)->gp->r2->val))

#define REGS_GET_R3_VAL(regs)                                                  \
  (!regs->gp->r3->is_negative ? (regs)->gp->r3->val                            \
                              : VM_NEGATE_BYTE((regs)->gp->r3->val))

vm_regs_t *vm_regs_init(void);
void vm_regs_destroy(vm_regs_t *regs);

vm_gp_regs_t *vm_gp_regs_init(void);
void vm_gp_regs_destroy(vm_gp_regs_t *gp);

#ifdef __cplusplus
}
#endif

#endif /* __REGS_H__ */
