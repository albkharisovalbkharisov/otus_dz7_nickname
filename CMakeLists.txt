cmake_minimum_required(VERSION 3.5)

project(nickname VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

add_executable(nickname nickname.cpp)

set_target_properties(nickname PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-ggdb"
    # COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-fsanitize=thread"
)

target_link_libraries(nickname
    ${CMAKE_THREAD_LIBS_INIT}
)


install(TARGETS nickname RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT albkharisov@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

