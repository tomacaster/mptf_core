# # tests/CMakeLists.txt

# # Ustawienie polityki CMP0135 na NOWE
# if(POLICY CMP0135)
#     cmake_policy(SET CMP0135 NEW)
# endif()

# # Włączanie testów
# enable_testing()

# # Włączenie modułu FetchContent
# include(FetchContent)

# # Deklarowanie GoogleTest jako zależności
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
# )

# # Pobranie i dostępność GoogleTest
# FetchContent_MakeAvailable(googletest)

# # Dodanie katalogów źródłowych dla testów
# file(GLOB TEST_SOURCES *.cpp)

# # Tworzenie wykonywalnego pliku testowego
# add_executable(test_myclass ${TEST_SOURCES})

# # Linkowanie z biblioteką common i Google Test
# target_link_libraries(test_myclass PRIVATE common_lib gtest_main)

# # Warunkowe linkowanie z bibliotekami platformowymi
# if(WIN32)
#     target_link_libraries(test_myclass PRIVATE windows_platform)
# elseif(UNIX AND NOT IDF_PATH)
#     target_link_libraries(test_myclass PRIVATE linux_platform)
# elseif(IDF_PATH)
#     target_link_libraries(test_myclass PRIVATE esp32_platform)
# endif()

# # Dodanie Google Test do CMake
# include(GoogleTest)
# gtest_discover_tests(test_myclass)

# # Dodawanie testów z użyciem narzędzi diagnostycznych
# if(ENABLE_VALGRIND AND UNIX)
#     add_test(NAME valgrind_test_mptf_core COMMAND valgrind --leak-check=full $<TARGET_FILE:test_myclass>)
# elseif(ENABLE_DR_MEMORY AND WIN32)
#     add_test(NAME drmemory_test_mptf_core COMMAND drmemory -batch -- $<TARGET_FILE:test_myclass>)
# endif()
