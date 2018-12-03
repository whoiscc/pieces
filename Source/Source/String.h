//
#ifndef PIECES_SOURCE_SOURCE_STRING_H
#define PIECES_SOURCE_SOURCE_STRING_H

#include "Core/Parser.h"
#include <string>

class StringSource : public Source {
public:
  StringSource(const std::string str);
  virtual char Get() const;
  virtual void Forward();
  virtual bool IsEnd() const;
  virtual Ptr<Source> Load(const std::string &path) const;
private:
  const std::string _source;
  int _current;
};

#endif
