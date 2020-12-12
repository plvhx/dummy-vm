#ifndef __UTIL_H__
#define __UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define VM_ALIGN_TO_BYTE(val)	((val) & 0xff)
#define VM_ALIGN_TO_WORD(val)	((val) & 0xffff)

#define VM_NEGATE_BYTE(val)		((0xff - VM_ALIGN_TO_BYTE(val)) - 0xff)
#define VM_NEGATE_WORD(val)		((0xffff - VM_ALIGN_TO_WORD(val)) - 0xffff)

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_H__ */
