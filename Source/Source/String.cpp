//
#include "Core/Base.h"
#include "Source/String.h"

StringSource::StringSource(const std::string str)
  : _source(str), _current(0)
{
  //
}

char StringSource::Get() const {
  // Debug("get position {0} = '{1}'({1:x})", _current, _source[_current]);
  Assert(_current < _source.length());
  return _source[_current];
}

void StringSource::Forward() {
  // Debug("forward");
  Assert(_current < _source.length());
  _current++;
}

bool StringSource::IsEnd() const {
  return _current == _source.length();
}

Ptr<Source> StringSource::Load(const std::string &path) const {
  throw NotImplemented();
}
