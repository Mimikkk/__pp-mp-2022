#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"
#include "../operators/nullary.hpp"
#include "../operators/unary.hpp"

fn random_sample(const Instance &instance, usize iterations) {

  var best_solution = instance.create_candidate(apply_random(instance));
  console::log("Solution with: %lu", best_solution.Makespan);

  while (--iterations) {
    let solution = instance.create_candidate(apply_random(instance));

    if (solution > best_solution) {
      best_solution = move(solution);
      console::log("New best solution with: %lu", best_solution.Makespan);
    }
  }

  return best_solution;
}