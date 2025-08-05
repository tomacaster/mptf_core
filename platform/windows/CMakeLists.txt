# platform/windows/CMakeLists.txt

# Zbieranie plików źródłowych i nagłówkowych
file(GLOB_RECURSE WINDOWS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

# Tworzenie biblioteki platformy Windows
add_library(windows_platform STATIC
    ${WINDOWS_SOURCES}
)

# Określenie katalogów nagłówkowych
target_include_directories(windows_platform PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Linkowanie bibliotek specyficznych dla Linux
target_link_libraries(windows_platform PRIVATE pthread)

# Dodanie zależności spdlog (która może wykorzystywać fmt)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# Linkowanie bibliotek spdlog i fmt
target_link_libraries(windows_platform PUBLIC spdlog::spdlog fmt::fmt)

# Definicje kompilatora specyficzne dla Windows
target_compile_definitions(windows_platform PRIVATE WINDOWS_PLATFORM)

# Linkowanie bibliotek specyficznych dla Windows, jeśli są potrzebne
# target_link_libraries(windows_platform PRIVATE some_windows_lib)
