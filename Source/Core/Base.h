//
#ifndef PIECES_SOURCE_CORE_BASE_H
#define PIECES_SOURCE_CORE_BASE_H

#include <memory>
#include <functional>
#include <exception>
#include <cassert>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Basic component of Pieces Programming Language.
class Piece;

// Container of Piece objects.
// Should implement garbage collecting function.
class Pool;

// Representation of source code of Pieces.
class Source;

template <typename T> using Ptr = std::unique_ptr<T>;

template <typename T>
inline auto &&Move(T &&arg) {
  return std::move(arg);
}

template <typename T> using Ref = std::reference_wrapper<T>;

class Exception : public std::exception {
public:
  Exception() : std::exception(), _message("PieceException") {
    //
  }
  virtual const char *what() const throw() {
    return _message.c_str();
  }
protected:
  void SetMessage(const std::string &message) {
    _message = message;
  }
private:
  std::string _message;
};

class NotImplemented : public Exception {
public:
  NotImplemented() {
    SetMessage("NotImplemented");
  }
};

template <typename T> inline void Assert(T &&expr) {

#ifndef PIECES_FLAG_PRODUCTION
  assert(expr);
#endif

}

class Logger {
public:
  Logger()
    : _logger(spdlog::stdout_color_mt("console"))
  {
    _logger->set_level(spdlog::level::debug);
  }
  static Logger &Get() {
    return _instance;
  }
  template <typename ...T> void Error(T... args) {
    _logger->error(args...);
  }
  template <typename ...T> void Warning(T... args) {
    _logger->warn(args...);
  }
  template <typename ...T> void Info(T... args) {
    _logger->info(args...);
  }
  template <typename ...T> void Debug(T... args) {
    _logger->debug(args...);
  }
private:
  std::shared_ptr<spdlog::logger> _logger;
  static Logger _instance;
};

template <typename ...T> void Error(T... args) {
  Logger::Get().Error(args...);
}

template <typename ...T> void Warning(T... args) {
  Logger::Get().Warning(args...);
}

template <typename ...T> void Info(T... args) {
  Logger::Get().Info(args...);
}

template <typename ...T> void Debug(T... args) {

#ifndef PIECES_FLAG_PRODUCTION
Logger::Get().Debug(args...);
#endif

}


#endif
