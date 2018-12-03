//
#include "Piece/Phantom.h"
#include "Core/Piece.h"

PhantomPiece::PhantomPiece(Pool &pool) : Piece(pool) {
  //
}

Ptr<const Piece> PhantomPiece::Apply(const Piece &other) const {
  throw PhantomGotApplied(*this, other);
}

PhantomGotApplied::PhantomGotApplied(
  const PhantomPiece &piece, const Piece &other
) : PieceException(piece), _appliee(other) {
  //
}

const Piece &PhantomGotApplied::GetAppliee() const {
  return _appliee;
}
