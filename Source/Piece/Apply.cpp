//
#include "Piece/Apply.h"

ApplyPiece::ApplyPiece(
  Pool &pool,
  const Piece &applier,
  const Piece &appliee
) : Piece(pool), _applier(applier), _appliee(appliee) {
  Hold(_applier);
  Hold(_appliee);
}

ApplyPiece::~ApplyPiece() {
  Drop(_applier);
  Drop(_appliee);
}
