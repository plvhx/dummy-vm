#ifndef __INSN_H__
#define __INSN_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum vm_insn {
	VM_INSN_STORE = 0x01,
	VM_INSN_LOAD = 0x02,
	VM_INSN_ADD_OP = 0x10,
	VM_INSN_SUB_OP = 0x11,
	VM_INSN_MUL_OP = 0x12,
	VM_INSN_DIV_OP = 0x13,
	VM_INSN_DISPLAY = 0x20,
} vm_insn_t;

#ifdef __cplusplus
}
#endif

#endif /* __INSN_H__ */
