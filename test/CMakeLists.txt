file(GLOB_RECURSE test_SRC
    "./*.cpp"
    )

file(GLOB_RECURSE test_HEADERS
    "./*.h"
    )

include_directories(../
    ./)

add_executable(test_cli gtest.cpp ${test_SRC} ${test_HEADERS} ../nicknametree.h ../nicknametree.cpp )

target_link_libraries(test_cli gtest)
