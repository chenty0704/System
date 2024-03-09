include(CMakeFindDependencyMacro)

set(Boost_NO_WARN_NEW_VERSIONS ON)

find_dependency(Boost REQUIRED COMPONENTS json)
find_dependency(GTest REQUIRED CONFIG)
find_dependency(mdspan REQUIRED CONFIG)

include("${CMAKE_CURRENT_LIST_DIR}/SystemTargets.cmake")
