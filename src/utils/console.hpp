#pragma once
#include "../imports.hpp"

namespace console {
  extern fn log(const char *format, ...) -> void;
  extern fn info(const char *format, ...) -> void;
  extern fn event(const char *format, ...) -> void;
  extern fn error(const char *format, ...) -> void;
}
