//
#include "../Piece.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <exception>


class SymbolPiece : public Piece {
public:
  static SymbolPiece &Get(std::string identifier);
  virtual std::unique_ptr<Piece> Apply(std::unique_ptr<Piece> other);
private:
  SymbolPiece(std::string identifier);
  std::string _identifier;
  static std::unordered_map<std::string, std::unique_ptr<SymbolPiece>> _table;
};
