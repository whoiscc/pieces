//
#ifndef PIECES_SOURCE_CORE_PIECE_H
#define PIECES_SOURCE_CORE_PIECE_H

#include "Core/Base.h"

class Piece {
public:
  virtual Ptr<const Piece> Apply(const Piece &other) const;
  virtual ~Piece();
protected:
  Piece(Pool &pool);
  void Hold(const Piece &piece);
  void Drop(const Piece &piece);
private:
  Pool &_pool;
};

class PieceException : public Exception {
public:
  PieceException(const Piece &piece);
  const Piece &GetPiece();
private:
  const Piece &_piece;
};

#endif
