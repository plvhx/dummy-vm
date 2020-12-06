#ifndef __UTIL_H__
#define __UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#define VM_ALIGN_TO_BYTE(val)	((val) & 0xff)
#define VM_NEGATE_BYTE(val)		(((val) - 1) - 0xff)

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_H__ */
