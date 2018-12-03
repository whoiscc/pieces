//
#include "Core/Parser.h"
#include "Core/Piece.h"
#include "Core/Pool.h"
#include "Piece/Apply.h"
#include "Piece/Function.h"
#include "Piece/Symbol.h"
#include "Piece/Phantom.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

void Source::ForwardExpect(char expected) {
  Forward();
  if (Get() != expected) {
    throw UnexpectedCharacter(*this, expected);
  }
}

namespace {
  const std::string _SPACE_CHAR(" \r\n\t");
  const std::string _IDENTIFIER_END("`.(),");

  void _SkipSpaces(Source &source) {
    while (!source.IsEnd() &&
        _SPACE_CHAR.find(source.Get()) != std::string::npos) {
      source.Forward();
    }
  }

  std::string _CoverIdentifier(Source &source) {
    std::string identifier;
    while (!source.IsEnd() &&
        (_SPACE_CHAR + _IDENTIFIER_END).find(source.Get())
          == std::string::npos) {
      identifier.append(1, source.Get());
      source.Forward();
    }
    return identifier;
  }
}

namespace {
  using _Context = std::vector<std::string>;

  const Piece &_ParseNext(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  );
  const Piece &_ParseApplySequence(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  );
  const Piece &_ParseFunction(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  );

  const Piece &_ParseNext(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  ) {
    _SkipSpaces(source);
    if (source.IsEnd()) {
      throw std::exception();
    }

    if (source.Get() == ';') {
      while (source.Get() != '\n') {
        source.Forward();
      }
      return _ParseNext(source, pool, context, parent);
    } else if (source.Get() == '`') {
      return _ParseFunction(source, pool, context, parent);
    } else if (source.Get() == '(') {
      source.ForwardExpect('(');
      const Piece &seq = _ParseApplySequence(source, pool, context, parent);
      source.ForwardExpect(')');
      return seq;
    } else if (source.Get() == ':') {
      source.ForwardExpect(':');
      std::string identifier = _CoverIdentifier(source);
      return SymbolPiece::Get(pool, parent, identifier);
    } else if (_IDENTIFIER_END.find(source.Get()) == std::string::npos) {
      std::string identifier = _CoverIdentifier(source);
      auto pos = std::find(context.rbegin(), context.rend(), identifier);
      if (pos == context.rend()) {
        throw std::exception();
      }
      const ArgumentPiece &piece = ArgumentPiece::Get(
        pool, parent, std::distance(pos, context.rbegin()));
      return piece;
    } else {
      throw std::exception();
    }
  }

  const Piece &_ParseApplySequence(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  ) {
    Ref<const Piece> result(_ParseNext(source, pool, context, parent));
    try {
      while (true) {
        const Piece &nextPiece = _ParseNext(source, pool, context, parent);
        Ptr<const Piece> appliedPiece =
          static_cast<const Piece &>(result).Apply(nextPiece);
        Ref<const Piece> piece_ref = pool.Add(Move(appliedPiece), parent);
        result = piece_ref;
      }
    } catch (std::exception) {
      return result;
    }
    throw std::exception();
  }

  const Piece &_ParseFunction(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  ) {
    source.ForwardExpect('`');
    std::string argument = _CoverIdentifier(source);
    context.push_back(argument);
    const Piece &body = _ParseApplySequence(source, pool, context, parent);
    context.pop_back();
    Ptr<const FunctionPiece> piece(new FunctionPiece(pool, body));
    return pool.Add(Move(piece), parent);
  }
}

const Piece &Parse(Source &source, Pool &pool, const Piece &parent) {
  _Context context;
  const Piece &phantom =
    pool.AddRoot(Ptr<const PhantomPiece>(new PhantomPiece(pool)));
  const Piece &parsed = _ParseApplySequence(source, pool, context, phantom);
  pool.Hold(parsed, parent);
  pool.DropRoot(phantom);
  return parsed;
}
