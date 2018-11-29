find_package(Catch2 REQUIRED)

include_directories(../Source)

add_executable(TestPieces Main.cpp TestSymbolPiece.cpp)

target_link_libraries(TestPieces Pieces Catch2::Catch2)
