//
#include "Apply.h"
#include <memory>


ApplyPiece::ApplyPiece(
  std::unique_ptr<Piece> applier,
  std::unique_ptr<Piece> appliee
) : _applier(std::move(applier)), _appliee(std::move(appliee))
{
  //
}
