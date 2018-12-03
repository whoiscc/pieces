//
#include "Pool/NeverDrop.h"

const Piece &NeverDropPool::Add(Ptr<const Piece> piece, const Piece &parent) {
  _data.push_back(Move(piece));
  return *_data.back();
}

const Piece &NeverDropPool::AddRoot(Ptr<const Piece> piece) {
  _data.push_back(Move(piece));
  return *_data.back();
}

void NeverDropPool::Hold(const Piece &piece, const Piece &owner) {
  //
}

void NeverDropPool::HoldRoot(const Piece &piece) {
  //
}

void NeverDropPool::Drop(const Piece &piece, const Piece &owner) {
  //
}

void NeverDropPool::DropRoot(const Piece &piece) {
  //
}
