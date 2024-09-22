# common/CMakeLists.txt

# Zbieranie plików źródłowych i nagłówkowych
file(GLOB_RECURSE COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

# Tworzenie biblioteki common
add_library(common_lib STATIC
    ${COMMON_SOURCES}
)

# Określenie katalogów nagłówkowych
target_include_directories(common_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Opcjonalne: dodawanie specyficznych ustawień lub zależności
