include_directories(.)

add_library(Pieces
  Core/Piece.cpp
  Core/Parser.cpp

  Piece/Apply.cpp
  Piece/Symbol.cpp
  Piece/Function.cpp
  Piece/Phantom.cpp

  Pool/NeverDrop.cpp
)
