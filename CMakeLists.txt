cmake_minimum_required(VERSION 3.16)
project(prack_numbers_system LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(prack_numbers_system
        main.cpp
        minimizator.cpp
        value_shape.cpp
        value_shape.h
        general_data.cpp
        general_data.h
        vals_table.cpp
        vals_table.h
        variable_in_function.cpp
        variable_in_function.h
        variable_combination.cpp
        variable_combination.h
        rounded_rectangle.cpp
        center_positioned_string.cpp
        center_positioned_string.h
        inoutput_field.cpp
        button.cpp)
target_link_libraries(prack_numbers_system PRIVATE sfml-graphics sfml-system sfml-window)
target_compile_features(prack_numbers_system PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
            TARGET prack_numbers_system
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:prack_numbers_system>
            VERBATIM)
endif()

install(TARGETS prack_numbers_system)