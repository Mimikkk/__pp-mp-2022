#pragma once
#include "../imports.hpp"

namespace thread {
  inline thread_local i32 ID = 0;

  inline fn initialize(i32 max_cores = omp_get_max_threads()) {
    #pragma omp parallel num_threads(max_cores) default(none)
    {
      ID = omp_get_thread_num();
    }
  }
}
