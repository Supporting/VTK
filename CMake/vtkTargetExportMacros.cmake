if(NOT VTK_INSTALL_EXPORT_NAME)
  set(VTK_INSTALL_EXPORT_NAME VTKTargets)
endif()

MACRO(VTK_ADD_LIBRARY name)
  ADD_LIBRARY(${name} ${ARGN})
  SET_PROPERTY(GLOBAL APPEND PROPERTY VTK_TARGETS ${name})
ENDMACRO(VTK_ADD_LIBRARY)

MACRO(VTK_ADD_EXECUTABLE name)
  ADD_EXECUTABLE(${name} ${ARGN})
  SET_PROPERTY(GLOBAL APPEND PROPERTY VTK_TARGETS ${name})
ENDMACRO(VTK_ADD_EXECUTABLE)
