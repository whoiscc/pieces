//
#ifndef PIECES_SOURCE_CORE_PARSEEXCEPTION_H
#define PIECES_SOURCE_CORE_PARSEEXCEPTION_H

#include "Core/Base.h"

class InvalidSyntax : public Exception {
public:
  InvalidSyntax(const Source &source);
  const Source &GetSource() const;
private:
  const Source &_source;
};

class UnexpectedCharacter : public InvalidSyntax {
public:
  UnexpectedCharacter(const Source &source, char expected);
  char ExpectedChar() const;
private:
  char _expected;
};



#endif
