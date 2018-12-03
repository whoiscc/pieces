//
#ifndef PIECES_SOURCE_POOL_H
#define PIECES_SOURCE_POOL_H

#include "Core/Base.h"

class Pool {
public:
  virtual const Piece &Add(Ptr<const Piece> piece, const Piece &parent) = 0;
  virtual const Piece &AddRoot(Ptr<const Piece> piece) = 0;
  virtual void Hold(const Piece &piece, const Piece &owner) = 0;
  virtual void HoldRoot(const Piece &piece) = 0;
  virtual void Drop(const Piece &piece, const Piece &owner) = 0;
  virtual void DropRoot(const Piece &piece) = 0;
};

#endif
