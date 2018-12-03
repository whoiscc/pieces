//
#ifndef PIECES_SOURCE_CORE_PARSEEXCEPTION_H
#define PIECES_SOURCE_CORE_PARSEEXCEPTION_H

#include "Core/Base.h"
#include <string>

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

class UnknownCharacter : public InvalidSyntax {
public:
  UnknownCharacter(const Source &source);
};

class UnexpectedIdentifier : public InvalidSyntax {
public:
  UnexpectedIdentifier(const Source &source, std::string identifier);
private:
  std::string _identifier;
};

#endif
