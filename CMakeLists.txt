cmake_minimum_required(VERSION 3.20)
project(compro_solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(C atcoder/ABC000-099/ABC022/C.cpp)
add_executable(A.solve atcoder/ABC200-299/ABC227/A.solve.cpp)
add_executable(B.solve atcoder/ABC200-299/ABC227/B.solve.cpp)
add_executable(C.solve atcoder/ABC200-299/ABC227/C.solve.cpp)
add_executable(D.solve atcoder/ABC200-299/ABC227/D.solve.cpp)