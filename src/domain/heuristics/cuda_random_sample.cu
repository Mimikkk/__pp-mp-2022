#include "../../imports.hpp"
#include "../instance.hpp"

#define cuda_fn __global__ void

cuda_fn find_makespan(usize **schedule, usize x, usize y, usize *makespan) {
  usize result = 0;
  for (i32 i = 0; i < x; ++i) if (schedule[i][y] > result) result = schedule[i][y];
  *makespan = result;
}

cuda_fn create_schedule_kernel() {
}

cuda_fn create_candidate_kernel() {
}

fn cuda_random_sample(const Instance &instance, f64 time) -> Candidate {
  vector<usize> order = {};
  vector<vector<usize>> schedule = {};
  return Candidate(order, schedule);
}
