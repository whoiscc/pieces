//
#ifndef PIECES_SOURCE_CORE_PARSER_H
#define PIECES_SOURCE_CORE_PARSER_H

#include "Core/Base.h"
#include "Core/ParseError.h"
#include <string>

class Source {
public:
  virtual char Get() const = 0;
  virtual void Forward() = 0;
  void ForwardExpect(char expected);
  virtual bool IsEnd() const = 0;
  virtual Ptr<Source> Load(const std::string &path) const = 0;
};

const Piece &Parse(Source &source, Pool &pool, const Piece &parent);

#endif
