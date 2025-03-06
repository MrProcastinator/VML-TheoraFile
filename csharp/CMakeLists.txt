# Enable asm for AOT library support
enable_language(ASM)

project(Theorafile-csharp)

set(LIBRARY_NAME Theorafile)
compile_mono_single_assembly_aot(
  CODE_FILE ${LIBRARY_NAME}
  FLAGS unsafe
  OPTIMIZE
)

# Static linking
add_library(VML${LIBRARY_NAME} STATIC
  ${LIBRARY_NAME}_static.c
  ${LIBRARY_NAME}_external.c
  ${LIBRARY_NAME}.dll.s
)

# Dynamic linking
add_library(VML${LIBRARY_NAME}_dynamic STATIC
  ${LIBRARY_NAME}_dynamic.c
  ${LIBRARY_NAME}_external.c
)

compile_mono_aot_dynamic(
  ASSEMBLY ${LIBRARY_NAME}
  STARTUP dynamic.c
  EXPORTS ${CMAKE_CURRENT_SOURCE_DIR}/exports.yml
  OPTIMIZE
)

install(
  TARGETS
    VML${LIBRARY_NAME}
    VML${LIBRARY_NAME}_dynamic
  DESTINATION lib
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}VML${LIBRARY_NAME}_stub.a
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}VML${LIBRARY_NAME}_stub_weak.a
  DESTINATION lib
)

install(
  FILES 
    ${CMAKE_BINARY_DIR}/${LIBRARY_NAME}.dll
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}.dll.suprx
  DESTINATION lib/mono
)

install(
  FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}.h
  DESTINATION include/VML
)
