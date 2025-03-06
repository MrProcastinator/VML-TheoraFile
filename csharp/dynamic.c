#include <psp2/kernel/modulemgr.h>

#define UNUSED(x) (void)(x)

/* Symbols for suprx compilation */

extern void __libc_init_array(void);
extern void __libc_fini_array(void);

void _init_vita_newlib(void) {}
void _free_vita_newlib(void) {}

void _fini(void) { }
void _init(void) { }

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void* args)
{
    UNUSED(argc);
    UNUSED(args);
    __libc_init_array();
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void* args)
{
    UNUSED(argc);
    UNUSED(args);
    __libc_fini_array();
    return SCE_KERNEL_STOP_SUCCESS;
}