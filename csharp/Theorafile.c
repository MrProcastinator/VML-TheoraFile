#include <mono/metadata/appdomain.h>
#include <mono/mini/jit.h>

#include "../theorafile.h"

extern void** mono_aot_module_Theorafile_info;

void VMLFNATheorafileRegister()
{
	mono_aot_register_module(mono_aot_module_Theorafile_info);

	mono_add_internal_call("Theorafile::INTERNAL_tf_open_callbacks", tf_open_callbacks);
	mono_add_internal_call("Theorafile::INTERNAL_tf_fopen", tf_fopen);
	mono_add_internal_call("Theorafile::INTERNAL_tf_fopen", tf_fopen);
	mono_add_internal_call("Theorafile::INTERNAL_tf_close", tf_close);
	mono_add_internal_call("Theorafile::tf_hasaudio", tf_hasaudio);
	mono_add_internal_call("Theorafile::tf_hasvideo", tf_hasvideo);
	mono_add_internal_call("Theorafile::tf_videoinfo", tf_videoinfo);
	mono_add_internal_call("Theorafile::tf_audioinfo", tf_audioinfo);
	mono_add_internal_call("Theorafile::tf_setaudiotrack", tf_setaudiotrack);
	mono_add_internal_call("Theorafile::tf_setvideotrack", tf_setvideotrack);
	mono_add_internal_call("Theorafile::tf_eos", tf_eos);
	mono_add_internal_call("Theorafile::tf_reset", tf_reset);
	mono_add_internal_call("Theorafile::tf_readvideo", tf_readvideo);
	mono_add_internal_call("Theorafile::tf_readaudio", tf_readaudio);
}