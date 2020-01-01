# Generated by Boost 1.72.0

# address-model=64

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "64 bit, need 32")
  return()
endif()

# layout=system

# toolset=gcc8

# link=shared

if(DEFINED Boost_USE_STATIC_LIBS)
  if(Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "shared, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(WIN32)
    _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "shared, default on Windows is static, set Boost_USE_STATIC_LIBS=OFF to override")
    return()
  endif()
endif()

# runtime-link=shared

if(Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "shared runtime, Boost_USE_STATIC_RUNTIME=${Boost_USE_STATIC_RUNTIME}")
  return()
endif()

# runtime-debugging=off

if(Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "release runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(NOT "${Boost_USE_MULTITHREADED}" STREQUAL "" AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=release

if(NOT "${Boost_USE_RELEASE_LIBS}" STREQUAL "" AND NOT Boost_USE_RELEASE_LIBS)
  _BOOST_SKIPPED("libboost_wserialization.so.1.72.0" "release, Boost_USE_RELEASE_LIBS=${Boost_USE_RELEASE_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_wserialization.so.1.72.0")
endif()

# Target file name: libboost_wserialization.so.1.72.0

get_target_property(__boost_imploc Boost::wserialization IMPORTED_LOCATION_RELEASE)
if(__boost_imploc)
  message(WARNING "Target Boost::wserialization already has an imported location '${__boost_imploc}', which will be overwritten with '${_BOOST_LIBDIR}/libboost_wserialization.so.1.72.0'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::wserialization APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

set_target_properties(Boost::wserialization PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE CXX
  IMPORTED_LOCATION_RELEASE "${_BOOST_LIBDIR}/libboost_wserialization.so.1.72.0"
  )

set_target_properties(Boost::wserialization PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

set_target_properties(Boost::wserialization PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "BOOST_WSERIALIZATION_DYN_LINK"
  )

list(APPEND _BOOST_WSERIALIZATION_DEPS serialization headers)
