cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(VMLBuild)

set(VITA OFF CACHE BOOL "Build for PSVita")

if(VITA)
	if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
		if(DEFINED ENV{VITASDK})
			set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
		else()
			message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
		endif()
	endif()
endif()

project(Theorafile)

# Options
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_TESTS "Build theora tests" OFF)

set(CMAKE_C_STANDARD 99)
if(BUILD_SHARED_LIBS)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Includes
set(INCLUDES "-I${SRCDIR} -I${SRCDIR}/lib -I${SRCDIR}/lib/ogg -I${SRCDIR}/lib/vorbis -I${SRCDIR}/lib/theora")

# Source
set(TFSRC_ARCH_GENERIC
    theorafile.c
    lib/ogg/bitwise.c
    lib/ogg/framing.c
    lib/vorbis/analysis.c
    lib/vorbis/bitrate.c
    lib/vorbis/block.c
    lib/vorbis/codebook.c
    lib/vorbis/envelope.c
    lib/vorbis/floor0.c
    lib/vorbis/floor1.c
    lib/vorbis/vinfo.c
    lib/vorbis/lookup.c
    lib/vorbis/lpc.c
    lib/vorbis/lsp.c
    lib/vorbis/mapping0.c
    lib/vorbis/mdct.c
    lib/vorbis/psy.c
    lib/vorbis/registry.c
    lib/vorbis/res0.c
    lib/vorbis/sharedbook.c
    lib/vorbis/smallft.c
    lib/vorbis/synthesis.c
    lib/vorbis/window.c
    lib/theora/apiwrapper.c
    lib/theora/bitpack.c
    lib/theora/decapiwrapper.c
    lib/theora/decinfo.c
    lib/theora/decode.c
    lib/theora/dequant.c
    lib/theora/fragment.c
    lib/theora/huffdec.c
    lib/theora/idct.c
    lib/theora/tinfo.c
    lib/theora/internal.c
    lib/theora/quant.c
    lib/theora/state.c
)
set(TFSRC_ARCH_X86
    lib/theora/x86/mmxfrag.c
    lib/theora/x86/mmxidct.c
    lib/theora/x86/mmxstate.c
    lib/theora/x86/sse2idct.c
    lib/theora/x86/x86cpu.c
    lib/theora/x86/x86state.c
)
set(TFSRC_ARCH_ARM
    lib/theora/arm-intrinsics/armcpu.c
    lib/theora/arm-intrinsics/armfrag.c
    lib/theora/arm-intrinsics/armidct.c
    lib/theora/arm-intrinsics/armloop.c
    lib/theora/arm-intrinsics/armstate.c
)

# Detect cross targets
if(WIN32 OR CYGWIN OR MINGW)
    set(WINDOWS_TARGET 1)
endif()
if(APPLE)
    set(APPLE_TARGET 1)
endif()
if(VITA)
    set(VITA_TARGET 1)
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(DEFINES ${DEFINES} -DOC_X86_ASM -DOC_X86_64_ASM)
    set(TFSRC_ARCH_OPT ${TFSRC_ARCH_X86})
endif()
if(CMAKE_SYSTEM_PROCESSOR MATCHES "i686")
    set(DEFINES ${DEFINES} -DOC_X86_ASM)
    set(TFSRC_ARCH_OPT ${TFSRC_ARCH_X86})
endif()
if(CMAKE_SYSTEM_PROCESSOR MATCHES "armv7")
    set(DEFINES ${DEFINES} -DOC_ARM_ASM -DOC_ARM_ASM_EDSP -DOC_ARM_ASM_MEDIA -DOC_ARM_ASM_NEON)
    set(TFSRC_ARCH_OPT ${TFSRC_ARCH_ARM})
endif()
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(DEFINES ${DEFINES} -DOC_ARM_ASM -DOC_ARM_ASM_EDSP -DOC_ARM_ASM_MEDIA -DOC_ARM_ASM_NEON)
    set(TFSRC_ARCH_OPT ${TFSRC_ARCH_ARM})
endif()

# Compiler
if(WINDOWS_TARGET)
    set(TARGET SHARED)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc")
elseif(APPLE_TARGET)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmacosx-version-min=10.9")
    set(TARGET SHARED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic -fPIC")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -install_name @rpath/libtheorafile.dylib")
elseif(VITA_TARGET)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -marm -mtune=cortex-a9 -mfpu=neon -Wno-incompatible-pointer-types -Wno-stringop-overflow -Wno-deprecated-declarations -Wl,-q -O3 -Wall")
    set(TARGET STATIC)
else()
    set(TARGET SHARED)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpic -fPIC")
endif()


# Targets
add_library(theorafile ${TARGET} ${TFSRC_ARCH_GENERIC} ${TFSRC_ARCH_OPT})
target_include_directories(theorafile PUBLIC ${INCLUDES})
target_compile_definitions(theorafile PUBLIC ${DEFINES})

if(BUILD_TESTS)
    add_executable(theorafile-test sdl2test/sdl2test.c)
    target_link_libraries(theorafile-test PRIVATE theorafile)
endif()

install(
    TARGETS theorafile
    DESTINATION lib
)

add_subdirectory(csharp)