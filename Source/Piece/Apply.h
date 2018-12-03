//
#ifndef PIECES_SOURCE_PIECE_APPLY_H
#define PIECES_SOURCE_PIECE_APPLY_H

#include "Core/Base.h"
#include "Core/Piece.h"
#include "Core/Pool.h"

class ApplyPiece : public Piece {
public:
  ApplyPiece(Pool &pool, const Piece &applier, const Piece &appliee);
  ~ApplyPiece();
private:
  const Piece &_applier, &_appliee;
};

#endif
