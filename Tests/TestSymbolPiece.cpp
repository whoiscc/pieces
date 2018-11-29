//
#include <catch2/catch.hpp>
#include "Piece/Symbol.h"
#include <memory>


TEST_CASE(
  "`SymbolPiece::Get` returns same instance for same name",
  "[SymbolPiece]"
) {
  SymbolPiece &piece1 = SymbolPiece::Get("something"),
    &piece2 = SymbolPiece::Get("something");
  REQUIRE(std::addressof(piece1) == std::addressof(piece2));

  SymbolPiece &piece3 = SymbolPiece::Get("other");
  REQUIRE(std::addressof(piece1) != std::addressof(piece3));

  SymbolPiece &piece4 = SymbolPiece::Get("something");
  REQUIRE(std::addressof(piece1) == std::addressof(piece4));
}
