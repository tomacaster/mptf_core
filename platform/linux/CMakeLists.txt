# platform/linux/CMakeLists.txt

# Zbieranie plików źródłowych i nagłówkowych
file(GLOB_RECURSE LINUX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

# Tworzenie biblioteki platformy Linux
add_library(linux_platform STATIC
    ${LINUX_SOURCES}
)

# Określenie katalogów nagłówkowych
target_include_directories(linux_platform PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Linkowanie bibliotek specyficznych dla Linux
target_link_libraries(linux_platform PRIVATE pthread)

# Dodanie zależności spdlog (która może wykorzystywać fmt)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# Linkowanie bibliotek spdlog i fmt
target_link_libraries(linux_platform PUBLIC spdlog::spdlog fmt::fmt)

# Opcjonalne: dodawanie definicji kompilatora specyficznych dla Linux
target_compile_definitions(linux_platform PRIVATE LINUX_PLATFORM)
