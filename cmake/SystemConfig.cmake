include(CMakeFindDependencyMacro)

find_dependency(Boost REQUIRED CONFIG COMPONENTS json)
find_dependency(GTest REQUIRED CONFIG)
find_dependency(mdspan REQUIRED CONFIG)

include("${CMAKE_CURRENT_LIST_DIR}/SystemTargets.cmake")
