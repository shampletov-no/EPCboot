#ifndef DEVVIRT_H
#define DEVVIRT_H

////BE CAREFUL! MSVC DON'T KNOW ABOUT "INLINE", ONLY "__INLINE"
#if defined(_MSC_VER)
#define inline __inline
#endif

#define ATOMIC_RUN(code) code

#define __ENABLE_IRQ
#define __DISABLE_IRQ



#endif