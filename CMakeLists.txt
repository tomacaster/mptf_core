cmake_minimum_required(VERSION 3.19)

# Define main variables
set(PROJECT_NAME mptf_core)
set(PROJECT_VERSION 0.0.2)
set(CONFIG_INSTALL_DIR lib/cmake/${PROJECT_NAME})

# Define the project
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add options for diagnostic tools
option(ENABLE_VALGRIND "Enable Valgrind for memory checking (Linux)" OFF)
option(ENABLE_DR_MEMORY "Enable Dr. Memory for memory checking (Windows)" OFF)

# Option for building documentation - domyślnie WYŁĄCZONE gdy używane jako podprojekt
option(BUILD_DOC "Build the documentation with Doxygen" OFF)

# Configure ProjectConfig.h
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config/ProjectConfig.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/common/include/ProjectConfig.h
  @ONLY
)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

# Configure README.md and CHANGELOG.md tylko jeśli pliki .in istnieją
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/README.md.in)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/README.md.in ${CMAKE_BINARY_DIR}/README.md @ONLY)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md.in)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md.in ${CMAKE_BINARY_DIR}/CHANGELOG.md @ONLY)
endif()

# Add subdirectories
add_subdirectory(common)
add_subdirectory(platform)

# Tylko jeśli chcemy budować testy - domyślnie WYŁĄCZONE
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

file(GLOB_RECURSE MPTF_CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/common/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform/src/*.cpp"
)

# Dodaj diagnostykę, aby upewnić się, że pliki źródłowe są znalezione
message(STATUS "MPTF_CORE_SOURCES: ${MPTF_CORE_SOURCES}")

if(NOT MPTF_CORE_SOURCES)
    message(FATAL_ERROR "No source files found for mptf_core")
endif()

# Definiowanie biblioteki mptf_core
add_library(mptf_core STATIC ${MPTF_CORE_SOURCES})

# Ustawienie include directories dla biblioteki
target_include_directories(mptf_core PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/include
)

# Ustawienie wymagań C++ dla biblioteki
target_compile_features(mptf_core PUBLIC cxx_std_23)

# Definiowanie aliasu targetu
add_library(mptf_core::mptf_core ALIAS mptf_core)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# Linkowanie bibliotek spdlog i fmt
target_link_libraries(mptf_core PUBLIC spdlog::spdlog fmt::fmt)

# Package configuration and installation - TYLKO jeśli instalujemy bibliotekę
option(INSTALL_MPTF_CORE "Install mptf_core library" OFF)
if(INSTALL_MPTF_CORE)
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
endif()

# Doxygen integration - TYLKO jeśli jawnie włączymy dokumentację
find_package(Doxygen)

if(DOXYGEN_FOUND AND BUILD_DOC)
    message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE}")

    # Set input directories for Doxygen
    set(DOXYGEN_INPUT_DIR_SPACE "${CMAKE_CURRENT_SOURCE_DIR}/common/include ${CMAKE_CURRENT_SOURCE_DIR}/platform/include")

    # Set the output directory for Doxygen documentation
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)

    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Configure Doxyfile
    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    # Configure README.md and CHANGELOG.md based on templates
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/update_readme.py)
    add_custom_target(update_readme
        COMMAND ${CMAKE_COMMAND} -E env python3 
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/update_readme.py 
            ${CMAKE_CURRENT_SOURCE_DIR}/README.md.in 
            ${CMAKE_BINARY_DIR}/README.md 
            ${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md
        COMMENT "Updating README.md and generating CHANGELOG.md for mptf_core"
    )

    # Copy README.md and CHANGELOG.md to the binary directory only
    add_custom_target(copy_docs
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/README.md
            ${CMAKE_BINARY_DIR}/README_FINAL.md
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/CHANGELOG.md
            ${CMAKE_BINARY_DIR}/CHANGELOG_FINAL.md
        COMMENT "Finalizing documentation for mptf_core"
    )
    
    add_dependencies(mptf_core_doc update_readme copy_docs)
endif()

    # Doxygen integration
    add_custom_target(mptf_core_doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Doxygen documentation for mptf_core"
        VERBATIM
    )

else()
    if(BUILD_DOC)
        message(WARNING "Doxygen not found. Documentation will not be generated.")
    endif()
endif()