include_directories(.)

add_library(Pieces
  Core/Piece.cpp
  Core/Parser.cpp
  Core/ParseError.cpp
  Core/Logger.cpp

  Piece/Apply.cpp
  Piece/Symbol.cpp
  Piece/Function.cpp
  Piece/Phantom.cpp

  Pool/NeverDrop.cpp

  Source/String.cpp
)
