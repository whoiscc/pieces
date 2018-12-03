//
#include "Core/Piece.h"
#include "Core/Pool.h"
#include "Piece/Apply.h"

Ptr<const Piece> Piece::Apply(const Piece &other) const {
  return Ptr<const Piece>(new ApplyPiece(_pool, *this, other));
}

Piece::Piece(Pool &pool) : _pool(pool) {}

void Piece::Hold(const Piece &piece) {
  _pool.Hold(piece, *this);
}

void Piece::Drop(const Piece &piece) {
  _pool.Drop(piece, *this);
}