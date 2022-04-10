#pragma once
#include "../imports.hpp"

namespace thread {
  inline thread_local i32 ID = 0;

  inline fn initialize() {
    #pragma omp parallel default(none)
    {
      ID = omp_get_thread_num();
    }
  }
}
