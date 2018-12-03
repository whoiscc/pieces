//
#ifndef PIECES_SOURCE_PIECE_SYMBOL_H
#define PIECES_SOURCE_PIECE_SYMBOL_H

#include "Core/Base.h"
#include "Core/Piece.h"
#include "Core/Pool.h"
#include <string>
#include <unordered_map>
#include <exception>

class SymbolPiece : public Piece {
public:
  static const SymbolPiece &Get(
    Pool &pool, const Piece &parent, const std::string &identifier
  );
  virtual Ptr<const Piece> Apply(const Piece &other) const;
  virtual ~SymbolPiece();
private:
  SymbolPiece(Pool &pool, std::string identifier);
  const std::string _identifier;
  static std::unordered_map<std::string, Ref<const SymbolPiece>> _table;
};

#endif
