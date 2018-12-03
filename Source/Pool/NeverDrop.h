//
#ifndef PIECES_SOURCE_POOL_NEVERDROP_H
#define PIECES_SOURCE_POOL_NEVERDROP_H

#include "Core/Base.h"
#include "Core/Piece.h"
#include "Core/Pool.h"
#include <vector>

class NeverDropPool : public Pool {
public:
  virtual const Piece &Add(Ptr<const Piece> piece, const Piece &parent);
  virtual const Piece &AddRoot(Ptr<const Piece> piece);
  virtual void Hold(const Piece &piece, const Piece &owner);
  virtual void HoldRoot(const Piece &piece);
  virtual void Drop(const Piece &piece, const Piece &owner);
  virtual void DropRoot(const Piece &piece);
private:
  std::vector<Ptr<const Piece>> _data;
};

#endif
