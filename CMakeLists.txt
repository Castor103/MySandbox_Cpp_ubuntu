# 프로젝트 정보
project( NST_Subsystem_Data_Simul_Project )

#set(CMAKE_C_COMPILER "gcc")

message(${CMAKE_PROJECT_NAME})
message(${PROJECT_BINARY_DIR})
cmake_minimum_required(VERSION 2.8)

set(ROOT ..)
set(LIB_DIR ${ROOT}/lib)
set(MAIN_DIR ${ROOT}/src)
set(COMMON_DIR ${ROOT}/common)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions( -DBOOST_LOG_DYN_LINK=1)
add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )

# unset(Boost_LIBRARIES)
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED ON)

add_definitions( -DDSM_TEST_DEFINE )

set(SOURCE 
    ${MAIN_DIR}/test_start.cpp
    ${MAIN_DIR}/test_init.cpp
    ${MAIN_DIR}/utils/a_1.cpp
    ${MAIN_DIR}/utils/interface/a_2.cpp
    )

set(OUTPUT program_out)
set(EXE_FILE program)

find_package(Boost REQUIRED COMPONENTS thread program_options system)

find_package(Threads REQUIRED)

add_compile_options(-W -Wall -lpthread -Wno-all)

include_directories(${COMMON_DIR})
add_executable(${OUTPUT} ${SOURCE})

target_link_libraries(${OUTPUT} PUBLIC Threads::Threads)

install(TARGETS ${OUTPUT} ${LIB_NAME}
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/build/bin
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/build/obj)
