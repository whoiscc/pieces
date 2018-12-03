//
#include <catch2/catch.hpp>
#include "Core/Piece.h"
#include "Core/Parser.h"
#include "Source/String.h"
#include "Pool/NeverDrop.h"
#include "Piece/Phantom.h"

TEST_CASE("parse simple code snippet successfully") {
  StringSource source("`x x. :something");
  NeverDropPool pool;
  const Piece &parent = pool.AddRoot(Ptr<const Piece>(new PhantomPiece(pool)));

  const Piece &parsed = Parse(source, pool, parent);
}
