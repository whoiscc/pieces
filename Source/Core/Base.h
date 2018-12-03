//
#ifndef PIECES_SOURCE_CORE_BASE_H
#define PIECES_SOURCE_CORE_BASE_H

#include <memory>
#include <functional>
#include <exception>

// Basic component of Pieces Programming Language.
class Piece;

// Container of Piece objects.
// Should implement garbage collecting function.
class Pool;

// Representation of source code of Pieces.
class Source;

template <typename T> using Ptr = std::unique_ptr<T>;

template <typename T>
inline auto &&Move(T &&arg) {
  return std::move(arg);
}

template <typename T> using Ref = std::reference_wrapper<T>;

class Exception : public std::exception {
  //
};

class PieceException : public Exception {
public:
  PieceException(const Piece &piece) : _piece(piece) {}
  const Piece &GetPiece() const { return _piece; }
private:
  const Piece &_piece;
};

#endif
