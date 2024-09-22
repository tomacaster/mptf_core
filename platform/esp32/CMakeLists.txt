# platform/esp32/CMakeLists.txt

# Sprawdzenie, czy ESP-IDF jest ustawiony
if(NOT IDF_PATH)
    message(FATAL_ERROR "ESP-IDF not found. Please set IDF_PATH environment variable.")
endif()

# Zbieranie plików źródłowych i nagłówkowych
file(GLOB_RECURSE ESP32_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

# Tworzenie biblioteki platformy ESP32
add_library(esp32_platform STATIC
    ${ESP32_SOURCES}
)

# Określenie katalogów nagłówkowych
target_include_directories(esp32_platform PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Definicje kompilatora specyficzne dla ESP32
target_compile_definitions(esp32_platform PRIVATE ESP32_PLATFORM)

# Linkowanie bibliotek specyficznych dla ESP32, jeśli są potrzebne
# target_link_libraries(esp32_platform PRIVATE some_esp32_lib)
