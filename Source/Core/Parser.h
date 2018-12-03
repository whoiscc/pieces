//
#ifndef PIECES_SOURCE_CORE_PARSER_H
#define PIECES_SOURCE_CORE_PARSER_H

#include "Core/Base.h"
#include <exception>
#include <string>

class Source {
public:
  virtual char Get() const = 0;
  virtual void Forward() = 0;
  virtual void ForwardExpect(char expected) = 0;
  virtual bool IsEnd() const = 0;
  virtual Ptr<Source> Load(const std::string &path) const = 0;
};

const Piece &Parse(Source &source, Pool &pool, const Piece &parent);

#endif
