# Generated by Boost 1.72.0

# address-model=64

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  _BOOST_SKIPPED("libboost_python36.a" "64 bit, need 32")
  return()
endif()

# python=3.6

if(Boost_PYTHON_VERSION)
  string(REGEX REPLACE "([0-9]+[.][0-9]+)([.].*)?" "\\1" __boost_pyver ${Boost_PYTHON_VERSION})
  if(NOT __boost_pyver VERSION_EQUAL "3.6")
    _BOOST_SKIPPED("libboost_python36.a" "3.6, Boost_PYTHON_VERSION=${Boost_PYTHON_VERSION}")
    return()
  endif()
endif()

# layout=system

# toolset=gcc8

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_python36.a" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32)
    _BOOST_SKIPPED("libboost_python36.a" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=shared

if(Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_python36.a" "shared runtime, Boost_USE_STATIC_RUNTIME=${Boost_USE_STATIC_RUNTIME}")
  return()
endif()

# runtime-debugging=off

if(Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_python36.a" "release runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(NOT "${Boost_USE_MULTITHREADED}" STREQUAL "" AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_python36.a" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=release

if(NOT "${Boost_USE_RELEASE_LIBS}" STREQUAL "" AND NOT Boost_USE_RELEASE_LIBS)
  _BOOST_SKIPPED("libboost_python36.a" "release, Boost_USE_RELEASE_LIBS=${Boost_USE_RELEASE_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_python36.a")
endif()

# Target file name: libboost_python36.a

get_target_property(__boost_imploc Boost::python IMPORTED_LOCATION_RELEASE)
if(__boost_imploc)
  message(WARNING "Target Boost::python already has an imported location '${__boost_imploc}', which will be overwritten with '${_BOOST_LIBDIR}/libboost_python36.a'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::python APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

set_target_properties(Boost::python PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE CXX
  IMPORTED_LOCATION_RELEASE "${_BOOST_LIBDIR}/libboost_python36.a"
  )

set_target_properties(Boost::python PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

list(APPEND _BOOST_PYTHON_DEPS headers)
