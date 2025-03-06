#include <mono/metadata/appdomain.h>
#include <mono/mini/jit.h>

#include "../theorafile.h"

extern void** mono_aot_module_Theorafile_info;
extern void VMLFNATheorafileRegisterCalls();

void VMLFNATheorafileRegister()
{
	mono_aot_register_module(mono_aot_module_Theorafile_info);
	VMLFNATheorafileRegisterCalls();
}