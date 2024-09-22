cmake_minimum_required(VERSION 3.19)

# Definiowanie głównych zmiennych
set(PROJECT_NAME mptf_core)
set(PROJECT_VERSION 0.0.1)
set(CONFIG_INSTALL_DIR lib/cmake/${PROJECT_NAME})

# Definiowanie projektu
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# Ustawienie standardu C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dodanie opcji włączenia narzędzi diagnostycznych
option(ENABLE_VALGRIND "Enable Valgrind for memory checking (Linux)" OFF)
option(ENABLE_DR_MEMORY "Enable Dr. Memory for memory checking (Windows)" OFF)

# Konfiguracja plików przed resztą konfiguracji
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Version.h
)

configure_file(${CMAKE_SOURCE_DIR}/README.md.in ${CMAKE_BINARY_DIR}/README.md @ONLY)

# Włączenie wsparcia dla ESP-IDF, jeśli jest wybrane
if(IDF_PATH)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
endif()

# Dodanie podkatalogów
add_subdirectory(common)
add_subdirectory(platform)
add_subdirectory(tests)

# Instalacja i eksportowanie konfiguracji pakietu
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/mptf_coreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CONFIG_INSTALL_DIR}
)
