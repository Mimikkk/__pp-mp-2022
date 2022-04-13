#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"
#include "../operators/nullary.hpp"
#include "../operators/unary.hpp"
#include "../../utils/color.hpp"

fn random_sample(const Instance &instance, usize iterations) {

  var best_solution = instance.create_candidate(apply_random(instance));
  console::info("Initial solution with: %s%lu", color::Silver, best_solution.Makespan);

  while (--iterations) {
    let solution = instance.create_candidate(apply_random(instance));

    if (solution > best_solution) {
      best_solution = move(solution);
      console::event("New best solution with: %s%lu", color::Silver, best_solution.Makespan);
    }
  }

  return best_solution;
}