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

# Opcja budowania dokumentacji
option(BUILD_DOC "Build the documentation with Doxygen" ON)

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

# Integracja Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND AND BUILD_DOC)
    message(STATUS "Doxygen znaleziony: ${DOXYGEN_EXECUTABLE}")

    # Ustawienie katalogów wejściowych dla Doxygen jako przestrzeń oddzielona spacjami
    set(DOXYGEN_INPUT_DIR_SPACE 
        "${CMAKE_SOURCE_DIR}/include" 
        "${CMAKE_SOURCE_DIR}/common" 
        "${CMAKE_SOURCE_DIR}/platform" 
        "${CMAKE_SOURCE_DIR}/tests"
    )

    # Zamiana średników na spacje
    string(REPLACE ";" " " DOXYGEN_INPUT_DIR_SPACE_STR "${DOXYGEN_INPUT_DIR_SPACE}")

    set(DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/docs)  # Dokumentacja w katalogu docs w głównym katalogu projektu

    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Konfiguracja pliku Doxyfile
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generowanie dokumentacji Doxygen"
        VERBATIM
    )

    # Opcjonalnie: Możesz usunąć poniższą linię, aby dokumentacja nie była budowana razem z głównym targetem
    # add_dependencies(mptf_core doc)
else()
    if(BUILD_DOC)
        message(WARNING "Doxygen nie został znaleziony. Dokumentacja nie zostanie wygenerowana.")
    endif()
endif()