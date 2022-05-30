#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"
#include "../operators/nullary.hpp"
#include "../operators/unary.hpp"
#include "../../utils/color.hpp"

fn passed(f64 since, i32 thread_count = 1) -> f64 {
  return since - std::clock() / (f64) CLOCKS_PER_SEC / (f64) thread_count;
}

fn random_sample(const Instance &instance, f64 time) {
  var best_solution = instance.create_candidate(apply_random(instance));
  console::info("Initial solution with: %s%lu", color::Silver, best_solution.Makespan);

  f64 current;
  while ((current = passed(time)) > 0) {
    let solution = instance.create_candidate(apply_random(instance));

    if (solution > best_solution) {
      best_solution = move(solution);
      console::event("New best solution with: %s%lu", color::Silver, best_solution.Makespan);
      console::event("Timestamp: %s%.2lf%s/%s%.2lf", color::Silver, time - current, color::Yellow, color::Silver, time);
    }
  }

  return best_solution;
}

#ifndef cuda
fn random_sample_threaded(const Instance &instance, f64 time, i32 *best_id) {
  var best_solution = instance.create_candidate(apply_random(instance));
  *best_id = omp_get_thread_num();

  console::info("Initial solution with: %s%lu", color::Silver, best_solution.Makespan);

  #pragma omp parallel default(shared)
  {
    loop {
      let solution = instance.create_candidate(apply_random(instance));

      if (solution > best_solution) {
        #pragma omp critical
        {
          if (solution > best_solution) {
            best_solution = move(solution);
            *best_id = omp_get_thread_num();

            console::event("New best solution with: %s%lu", color::Silver, best_solution.Makespan);
            console::event("Timestamp: %s%.2lf%s/%s%.2lf",
                           color::Silver, passed(time, omp_get_num_threads()), color::Yellow, color::Silver, time);
          }
        }
      }

      if (passed(time, omp_get_num_threads()) <= 0) break;
    }
  }

  return best_solution;
}
#endif
