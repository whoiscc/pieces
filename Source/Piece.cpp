//
#include "Piece.h"
#include "Piece/Apply.h"
#include <memory>


std::unique_ptr<Piece> Piece::Apply(std::unique_ptr<Piece> other) {
  return std::make_unique<Piece>(
    ApplyPiece(std::unique_ptr<Piece>(this), std::move(other)));
}
