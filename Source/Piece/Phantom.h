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

class PhantomGotApplied : public PieceException {
public:
  PhantomGotApplied(const PhantomPiece &piece, const Piece &appliee);
  const Piece &GetAppliee() const;
private:
  const Piece &_appliee;
};

#endif
