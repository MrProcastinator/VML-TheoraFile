# Enable asm for AOT library support
enable_language(ASM)

project(Theorafile-csharp)

set(LIBRARY_NAME Theorafile)
compile_mono_single_assembly_aot(
  CODE_FILE ${LIBRARY_NAME}
  FLAGS unsafe
)
add_library(VML${LIBRARY_NAME} STATIC
  ${LIBRARY_NAME}.c
  ${LIBRARY_NAME}.dll.s
)

install(
  TARGETS VML${LIBRARY_NAME}
  DESTINATION lib
)

install(
  FILES 
    ${CMAKE_BINARY_DIR}/${LIBRARY_NAME}.dll 
  DESTINATION lib/mono
)

install(
  FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}.h
  DESTINATION include/VML
)
