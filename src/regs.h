#ifndef __REGS_H__
#define __REGS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef union vm_gp_regs {
	unsigned short r0;
	unsigned short r1;
	unsigned short r2;
	unsigned short r3;
} vm_gp_regs_t;

typedef struct vm_regs {
	vm_gp_regs_t gp;
} vm_regs_t;

#define REGS_GET_GP_R0(regs)	((regs)->gp.r0)
#define REGS_GET_GP_R1(regs)	((regs)->gp.r1)
#define REGS_GET_GP_R2(regs)	((regs)->gp.r2)
#define REGS_GET_GP_R3(regs)	((regs)->gp.r3)

vm_regs_t *vm_regs_init(void);
void vm_regs_destroy(vm_regs_t *regs);

#ifdef __cplusplus
}
#endif

#endif /* __REGS_H__ */
