add_library(System INTERFACE)
target_compile_features(System INTERFACE cxx_std_23)
target_include_directories(System INTERFACE $<INSTALL_INTERFACE:include>)
target_sources(System INTERFACE FILE_SET HEADERS FILES
        System/JSON.h
        System/MDArray.h
        System/Reflection.h
        System/System.h)
target_precompile_headers(System INTERFACE $<INSTALL_INTERFACE:System/System.h>)
target_link_libraries(System INTERFACE
        Boost::headers
        Boost::json
        std::mdspan)

install(TARGETS System EXPORT SystemTargets
        FILE_SET HEADERS)
install(EXPORT SystemTargets DESTINATION share/System
        NAMESPACE System::)
