#include "../imports.hpp"
#include "console.hpp"
#include "color.hpp"

namespace console {
  using namespace color;
  #define printfln(fmt)               \
    do {                              \
    va_list arguments;                \
    va_start(arguments, format);      \
    vfprintf(stdout, str("%s%s.%s\n", fmt, Yellow, Reset).get(), arguments); \
    va_end(arguments);                \
    } while (false)

  fn nfo() {
    return str("%s:", Yellow);
  }

  fn log(const char *format, ...) -> void {
    printfln(str("%sLog   %s %s%s", Magenta, nfo().get(), Cyan, format).get());
  }

  fn info(const char *format, ...) -> void {
    printfln(str("%sInfo  %s %s%s", Gray, nfo().get(), Gray, format).get());
  }

  fn event(const char *format, ...) -> void {
    printfln(str("%sEvent %s %s%s", Green, nfo().get(), Green, format).get());
  }

  fn error(const char *format, ...) -> void {
    printfln(str("%sError %s %s%s", Red, nfo().get(), Red, format).get());
  }
}
