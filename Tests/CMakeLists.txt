include_directories(../Source)

add_executable(TestPieces Main.cpp
  TestSymbolPiece.cpp
  TestParse.cpp
)

target_link_libraries(TestPieces Pieces)
