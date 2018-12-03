//
#include "Piece/Symbol.h"

std::unordered_map<
  std::string,
  Ref<const SymbolPiece>
> SymbolPiece::_table;

SymbolPiece const &SymbolPiece::Get(
  Pool &pool,
  const Piece &parent,
  const std::string &identifier
) {
  if (_table.count(identifier) == 0) {
    Ptr<const SymbolPiece> piece(new SymbolPiece(pool, identifier));
    const SymbolPiece &piece_ref =
      dynamic_cast<const SymbolPiece &>(pool.Add(Move(piece), parent));
    _table.insert({ identifier, piece_ref });
  }
  return _table.at(identifier);
}

Ptr<const Piece> SymbolPiece::Apply(const Piece &other) const {
  throw std::exception();
}

SymbolPiece::SymbolPiece(Pool &pool, std::string identifier)
  : Piece(pool), _identifier(identifier)
{
  //
}

SymbolPiece::~SymbolPiece() {
  _table.erase(_identifier);
}
