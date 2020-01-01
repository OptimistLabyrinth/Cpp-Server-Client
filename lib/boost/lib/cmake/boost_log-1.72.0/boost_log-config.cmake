# Generated by Boost 1.72.0

if(TARGET Boost::log)
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "Found boost_log ${boost_log_VERSION} at ${boost_log_DIR}")
endif()

# Compute the include and library directories relative to this file.

get_filename_component(_BOOST_CMAKEDIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

# If the computed and the original directories are symlink-equivalent, use original
if(EXISTS "/home/ksyoo/ksyooF/lib/boost/lib/cmake")
  get_filename_component(_BOOST_CMAKEDIR_COMPUTED "${_BOOST_CMAKEDIR}" REALPATH)
  get_filename_component(_BOOST_CMAKEDIR_ORIGINAL "/home/ksyoo/ksyooF/lib/boost/lib/cmake" REALPATH)
  if(_BOOST_CMAKEDIR_COMPUTED STREQUAL _BOOST_CMAKEDIR_ORIGINAL)
    set(_BOOST_CMAKEDIR "/home/ksyoo/ksyooF/lib/boost/lib/cmake")
  endif()
  unset(_BOOST_CMAKEDIR_COMPUTED)
  unset(_BOOST_CMAKEDIR_ORIGINAL)
endif()

get_filename_component(_BOOST_INCLUDEDIR "${_BOOST_CMAKEDIR}/../../include/" ABSOLUTE)
get_filename_component(_BOOST_LIBDIR "${_BOOST_CMAKEDIR}/../" ABSOLUTE)

# Create imported target Boost::log

add_library(Boost::log UNKNOWN IMPORTED)

set_target_properties(Boost::log PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
  INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB"
)

include(${CMAKE_CURRENT_LIST_DIR}/../BoostDetectToolset-1.72.0.cmake)

if(Boost_DEBUG)
  message(STATUS "Scanning ${CMAKE_CURRENT_LIST_DIR}/libboost_log-variant*.cmake")
endif()

file(GLOB __boost_variants "${CMAKE_CURRENT_LIST_DIR}/libboost_log-variant*.cmake")

macro(_BOOST_SKIPPED fname reason)
  if(Boost_VERBOSE OR Boost_DEBUG)
    message(STATUS "  [ ] ${fname}")
  endif()
  list(APPEND __boost_skipped "${fname} (${reason})")
endmacro()

foreach(f IN LISTS __boost_variants)
  if(Boost_DEBUG)
    message(STATUS "  Including ${f}")
  endif()
  include(${f})
endforeach()

unset(_BOOST_LIBDIR)
unset(_BOOST_INCLUDEDIR)
unset(_BOOST_CMAKEDIR)

get_target_property(__boost_configs Boost::log IMPORTED_CONFIGURATIONS)

if(__boost_variants AND NOT __boost_configs)
  set(__boost_message "No suitable build variant has been found.")
  if(__boost_skipped)
    set(__boost_message "${__boost_message}\nThe following variants have been tried and rejected:")
    foreach(s IN LISTS __boost_skipped)
      set(__boost_message "${__boost_message}\n* ${s}")
    endforeach()
  endif()
  set(boost_log_FOUND 0)
  set(boost_log_NOT_FOUND_MESSAGE ${__boost_message})
  unset(__boost_message)
  unset(__boost_skipped)
  unset(__boost_configs)
  unset(__boost_variants)
  unset(_BOOST_LOG_DEPS)
  return()
endif()

unset(__boost_skipped)
unset(__boost_configs)
unset(__boost_variants)

if(_BOOST_LOG_DEPS)
  list(REMOVE_DUPLICATES _BOOST_LOG_DEPS)
  if(Boost_VERBOSE OR Boost_DEBUG)
    message(STATUS "Adding boost_log dependencies: ${_BOOST_LOG_DEPS}")
  endif()
endif()

foreach(dep_boost_log IN LISTS _BOOST_LOG_DEPS)
  set(_BOOST_QUIET)
  if(boost_log_FIND_QUIETLY)
    set(_BOOST_QUIET QUIET)
  endif()
  set(_BOOST_REQUIRED)
  if(boost_log_FIND_REQUIRED)
    set(_BOOST_REQUIRED REQUIRED)
  endif()
  get_filename_component(_BOOST_CMAKEDIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)
  find_package(boost_${dep_boost_log} 1.72.0 EXACT CONFIG ${_BOOST_REQUIRED} ${_BOOST_QUIET} HINTS ${_BOOST_CMAKEDIR})
  set_property(TARGET Boost::log APPEND PROPERTY INTERFACE_LINK_LIBRARIES Boost::${dep_boost_log})
  unset(_BOOST_QUIET)
  unset(_BOOST_REQUIRED)
  unset(_BOOST_CMAKEDIR)
  if(NOT boost_${dep_boost_log}_FOUND)
    set(boost_log_FOUND 0)
    set(boost_log_NOT_FOUND_MESSAGE "A required dependency, boost_${dep_boost_log}, has not been found.")
    unset(_BOOST_LOG_DEPS)
    return()
  endif()
endforeach()

unset(_BOOST_LOG_DEPS)

mark_as_advanced(boost_log_DIR)
