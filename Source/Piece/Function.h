//
#ifndef PIECES_SOURCE_PIECE_FUNCTION_H
#define PIECES_SOURCE_PIECE_FUNCTION_H

#include "Core/Base.h"
#include "Core/Piece.h"
#include "Core/Pool.h"
#include <unordered_map>

class ArgumentPiece: public Piece {
public:
  static const ArgumentPiece &Get(Pool &pool, const Piece &parent, int depth);
private:
  ArgumentPiece(Pool &pool, int depth);
  int _depth;
  static std::unordered_map<int, Ref<const ArgumentPiece>> _table;
};

class FunctionPiece: public Piece {
public:
  FunctionPiece(Pool &pool, const Piece &body);
private:
  const Piece &_body;
};

#endif
