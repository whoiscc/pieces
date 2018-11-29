//
#ifndef PIECES_SOURCE_PIECE_H
#define PIECES_SOURCE_PIECE_H

#include <memory>


class Piece {
public:
  virtual std::unique_ptr<Piece> Apply(std::unique_ptr<Piece> other);
};

#endif
