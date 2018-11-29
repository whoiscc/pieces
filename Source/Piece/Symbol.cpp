//
#include "Symbol.h"
#include <memory>


std::unordered_map<
  std::string,
  std::unique_ptr<SymbolPiece>
> SymbolPiece::_table;

SymbolPiece &SymbolPiece::Get(std::string identifier) {
  if (_table.count(identifier) == 0) {
    _table[identifier] = std::make_unique<SymbolPiece>(SymbolPiece(identifier));
  }
  return *_table[identifier];
}

std::unique_ptr<Piece> SymbolPiece::Apply(std::unique_ptr<Piece> other) {
  throw std::exception();
}

SymbolPiece::SymbolPiece(std::string identifier)
  : _identifier(identifier)
{
  //
}
