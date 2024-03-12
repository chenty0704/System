set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/include")

add_library(System)
target_include_directories(System PUBLIC
        "$<BUILD_INTERFACE:${HEADERS_DIR}>"
        "$<INSTALL_INTERFACE:include>")
target_sources(System PUBLIC
        FILE_SET HEADERS BASE_DIRS "${HEADERS_DIR}" FILES
        "${HEADERS_DIR}/boost/system/result.hpp"
        "${HEADERS_DIR}/System/Macros.h"
        FILE_SET CXX_MODULES FILES
        "Base.ixx"
        "JSON.ixx"
        "Math.ixx"
        "MDArray.ixx"
        "System.ixx")
target_link_libraries(System PUBLIC
        Boost::headers
        Boost::json
        std::mdspan)
target_compile_features(System PUBLIC cxx_std_23)
target_compile_options(System PUBLIC /arch:AVX2 /W4 /WX)
target_link_options(System PUBLIC /WX)

install(TARGETS System EXPORT SystemTargets
        FILE_SET HEADERS
        FILE_SET CXX_MODULES DESTINATION "modules/System")
install(EXPORT SystemTargets DESTINATION "share/System"
        NAMESPACE System::)
