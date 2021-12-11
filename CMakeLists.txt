cmake_minimum_required(VERSION 3.14)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(/opt/X11/include)
link_directories(/opt/x11/lib)

add_executable(chess main.cpp subject.cpp subject.h observer.h piece.h piece.cpp board.cpp board.h strategy.h human.cpp human.h level1.cpp level1.h level2.cpp level2.h level3.cpp level3.h strategy.cpp king.cpp king.h queen.cpp queen.h bishop.cpp bishop.h rook.cpp rook.h knight.cpp knight.h pawn.cpp pawn.h graphobserver.cpp graphobserver.h textobserver.cpp textobserver.h window.cpp window.h)
target_link_libraries(chess -lx11)