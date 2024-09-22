# platform/CMakeLists.txt

if(IDF_PATH)
    add_subdirectory(esp32)
elseif(WIN32)
    add_subdirectory(windows)
elseif(UNIX)
    add_subdirectory(linux)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
