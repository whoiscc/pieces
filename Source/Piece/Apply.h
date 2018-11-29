//
#ifndef PIECES_SOURCE_PIECE_APPLY_H
#define PIECES_SOURCE_PIECE_APPLY_H

#include "../Piece.h"
#include <memory>


class ApplyPiece : public Piece {
public:
  ApplyPiece(std::unique_ptr<Piece> applier, std::unique_ptr<Piece> appliee);
private:
  std::unique_ptr<Piece> _applier, _appliee;
};

#endif
