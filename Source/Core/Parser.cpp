//
#include "Core/Base.h"
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
  if (IsEnd() || Get() != expected) {
    throw UnexpectedCharacter(*this, expected);
  }
  Forward();
}

class NoMorePiece : public Exception {
public:
  NoMorePiece() {
    SetMessage("NoMorePiece");
  }
};

namespace {
  const std::string _SPACE_CHAR(" \r\n\t");
  const std::string _SEQUENCE_BEGIN("`(");
  const std::string _SEQUENCE_END(".),");
  const std::string _IDENTIFIER_END =
    _SPACE_CHAR + _SEQUENCE_BEGIN + _SEQUENCE_END;

  bool _Contains(const std::string &charset, char c) {
    return charset.find(c) != std::string::npos;
  }

  void _SkipSpaces(Source &source) {
    while (!source.IsEnd() && _Contains(_SPACE_CHAR, source.Get())) {
      source.Forward();
      // Debug("forward");
    }
    Debug("skipped space");
  }

  std::string _CoverIdentifier(Source &source) {
    std::string identifier;
    while (!source.IsEnd() && !_Contains(_IDENTIFIER_END, source.Get())) {
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
      throw NoMorePiece();
    }

    Debug("source current: '{0}'({0:x})", source.Get());

    if (source.Get() == ';') {
      Debug("skip a comment");
      while (!source.IsEnd() && source.Get() != '\n') {
        source.Forward();
      }
      return _ParseNext(source, pool, context, parent);
    } else if (source.Get() == '`') {
      Debug("start parsing a function");
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
    } else if (!_Contains(_IDENTIFIER_END, source.Get())) {
      std::string identifier = _CoverIdentifier(source);
      auto pos = std::find(context.rbegin(), context.rend(), identifier);
      if (pos == context.rend()) {
        throw UnexpectedIdentifier(source, identifier);
      }
      const ArgumentPiece &piece = ArgumentPiece::Get(
        pool, parent, std::distance(pos, context.rbegin()));
      Debug("returning ArgumentPiece");
      return piece;
    } else {
      Debug("found unknown character");
      throw UnknownCharacter(source);
    }
  }

  const Piece &_ParseApplySequence(
    Source &source, Pool &pool, _Context &context, const Piece &parent
  ) {
    Ref<const Piece> result(_ParseNext(source, pool, context, parent));
    try {
      while (true) {
        Debug("begin _ParseApplySequence loop");
        const Piece &nextPiece = _ParseNext(source, pool, context, parent);
        Debug("before applying");
        Ptr<const Piece> appliedPiece =
          static_cast<const Piece &>(result).Apply(nextPiece);
        Debug("after applying");
        Ref<const Piece> piece_ref = pool.Add(Move(appliedPiece), parent);
        result = piece_ref;
        Debug("end _ParseApplySequence loop");
      }
    } catch (NoMorePiece) {
      return result;
    } catch (UnknownCharacter &ex) {
      if (_Contains(_SEQUENCE_END, source.Get())) {
        return result;
      } else {
        throw ex;
      }
    }
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
  Debug("start paring");

  _Context context;
  const Piece &phantom =
    pool.AddRoot(Ptr<const PhantomPiece>(new PhantomPiece(pool)));
  const Piece &parsed = _ParseApplySequence(source, pool, context, phantom);
  pool.Hold(parsed, parent);
  pool.DropRoot(phantom);
  return parsed;
}
