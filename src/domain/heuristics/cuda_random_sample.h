#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"

namespace cuda {
  fn random_sample(const Instance &instance, f64 time) -> Candidate;
}
