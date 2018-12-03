//
#include <catch2/catch.hpp>
#include "Pool/NeverDrop.h"
#include "Piece/Symbol.h"
#include "Piece/Phantom.h"
#include <memory>

TEST_CASE("`SymbolPiece::Get` returns same instance for same name") {
  NeverDropPool pool;
  const Piece &parent = pool.AddRoot(Ptr<const Piece>(new PhantomPiece(pool)));
  const SymbolPiece &piece1 = SymbolPiece::Get(pool, parent, "something"),
    &piece2 = SymbolPiece::Get(pool, parent, "something");
  REQUIRE(std::addressof(piece1) == std::addressof(piece2));

  const SymbolPiece &piece3 = SymbolPiece::Get(pool, parent, "other");
  REQUIRE(std::addressof(piece1) != std::addressof(piece3));

  const SymbolPiece &piece4 = SymbolPiece::Get(pool, parent, "something");
  REQUIRE(std::addressof(piece1) == std::addressof(piece4));
}
