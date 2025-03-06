#include <mono/metadata/appdomain.h>
#include <mono/mini/jit.h>

#include "../theorafile.h"

extern void VMLFNATheorafileRegisterCalls();

void VMLFNATheorafileRegisterDynamic()
{
	VMLFNATheorafileRegisterCalls();
}