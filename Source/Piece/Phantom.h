//
#ifndef PIECES_SOURCE_PIECE_PHANTOM_H
#define PIECES_SOURCE_PIECE_PHANTOM_H

#include "Core/Base.h"
#include "Core/Piece.h"

class PhantomPiece : public Piece {
public:
  PhantomPiece(Pool &pool);
  virtual Ptr<const Piece> Apply(const Piece &other) const;
};

class PhantomPieceIsApplied : public PieceException {
public:
  PhantomPieceIsApplied(const PhantomPiece &piece);
};

#endif
