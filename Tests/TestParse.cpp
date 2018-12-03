//
#include <catch2/catch.hpp>
#include "Core/Piece.h"
#include "Core/Parser.h"
#include "Source/String.h"
#include "Pool/NeverDrop.h"
#include "Piece/Phantom.h"

TEST_CASE("parse simple code snippet successfully") {
  const char *snippets[] = {
    "`x x. :something",
    "`sym `id id sym.. :something `x x."
  };

  for (int i = 0; i < sizeof(snippets) / sizeof(char *); i++) {
    StringSource source(snippets[i]);
    NeverDropPool pool;
    const Piece &parent =
      pool.AddRoot(Ptr<const Piece>(new PhantomPiece(pool)));
    const Piece &parsed = Parse(source, pool, parent);
  }
}
