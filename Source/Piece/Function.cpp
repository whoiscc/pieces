//
#include "Piece/Function.h"

std::unordered_map<int, Ref<const ArgumentPiece>> ArgumentPiece::_table;

const ArgumentPiece &ArgumentPiece::Get(
  Pool &pool, const Piece &parent, int depth
) {
  if (_table.count(depth) == 0) {
    Ptr<const ArgumentPiece> piece(new ArgumentPiece(pool, depth));
    const ArgumentPiece &piece_ref =
      dynamic_cast<const ArgumentPiece &>(pool.Add(Move(piece), parent));
    _table.insert({ depth, piece_ref });
  }
  return _table.at(depth);
}

ArgumentPiece::ArgumentPiece(Pool &pool, int depth)
  : Piece(pool), _depth(depth)
{
  //
}

FunctionPiece::FunctionPiece(Pool &pool, const Piece &body)
  : Piece(pool), _body(body)
{
  Hold(_body);
}
