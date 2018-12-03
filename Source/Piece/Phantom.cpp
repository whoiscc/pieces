//
#include "Piece/Phantom.h"
#include "Core/Piece.h"

PhantomPiece::PhantomPiece(Pool &pool) : Piece(pool) {
  //
}

Ptr<const Piece> PhantomPiece::Apply(const Piece &other) const {
  throw PhantomPieceIsApplied(*this);
}

PhantomPieceIsApplied::PhantomPieceIsApplied(const PhantomPiece &piece)
  : PieceException(piece)
{
  //
}
