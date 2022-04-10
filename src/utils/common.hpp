#pragma once
#include "../imports.hpp"
#include <stdnoreturn.h>

using std::optional;
using std::vector;

template<typename Tp, typename Dp = std::default_delete<Tp>>
using uptr = std::unique_ptr<Tp, Dp>;

template<typename Tp>
using sptr = std::shared_ptr<Tp>;
using std::move;

typedef double f64;
typedef float f32;

typedef size_t usize;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef char byte;
typedef unsigned char ubyte;

#define var auto
#define let const var
#define loop for(;;)
#define fn auto

inline fn str(const char *format, ...) {
  va_list arguments, size_check;
  va_start(arguments, format);
  va_copy(size_check, arguments);
  var size = vsnprintf(nullptr, 0, format, size_check);

  uptr<char> buffer{new char[size + 1]};
  vsprintf(buffer.get(), format, arguments);
  va_end(arguments);
  return buffer;
}
