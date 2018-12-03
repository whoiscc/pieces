//
#include "Core/ParseError.h"
#include "Core/Parser.h"
#include <sstream>

InvalidSyntax::InvalidSyntax(const Source &source) : _source(source) {
  SetMessage("InvalidSyntax");
}

const Source &InvalidSyntax::GetSource() const {
  return _source;
}

UnexpectedCharacter::UnexpectedCharacter(
  const Source &source, char expected
) : InvalidSyntax(source), _expected(expected) {
  std::stringstream output;
  output << "UnexpectedCharacter { get = '" << source.Get() <<
    "', expect = '" << expected << "' }";
  SetMessage(output.str());
}

char UnexpectedCharacter::ExpectedChar() const {
  return _expected;
}

UnknownCharacter::UnknownCharacter(const Source &source)
  : InvalidSyntax(source)
{
  std::stringstream output;
  output << "UnknownCharacter { get = '" << source.Get() << "' }";
  SetMessage(output.str());
}

UnexpectedIdentifier::UnexpectedIdentifier(
  const Source &source, std::string identifier
) : InvalidSyntax(source), _identifier(identifier) {
  std::stringstream output;
  output << "UnknownIdentifier { get = '" << source.Get() << "' }";
  SetMessage(output.str());
}
