#ifndef DEVVIRT_H
#define DEVVIRT_H

////BE CAREFUL! MSVC DON'T KNOW ABOUT "INLINE", ONLY "__INLINE"
#define inline
  #if defined(_MSC_VER)
    __inline
  #else
    inline
  #endif

#define ATOMIC_RUN(code) code

#define __ENABLE_IRQ()
#define __DISABLE_IRQ()



#endif