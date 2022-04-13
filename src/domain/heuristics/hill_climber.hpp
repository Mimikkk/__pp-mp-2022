#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"
#include "../operators/nullary.hpp"
#include "../operators/unary.hpp"
#include "../operators/binary.hpp"
#include "../../utils/color.hpp"

fn hill_climber(const Instance &instance, usize iterations, usize reset_threshold) {
  var best = instance.create_candidate(apply_random(instance));
  console::info("Initial solution with: %s%lu", color::Silver, best.Makespan);
  var prev = best;

  let initial_threshold = reset_threshold;
  while (--iterations) {
    if (not reset_threshold) {
      prev = instance.create_candidate(apply_random(instance));
      reset_threshold = initial_threshold;
    }

    let next = instance.create_candidate(apply_1swap(instance, prev.Order));

    if (next > prev) prev = move(next);
    if (prev > best) {
      best = prev;
      reset_threshold = initial_threshold;
      console::event("New best solution with: %s%lu", color::Silver, best.Makespan);
    }
  }

  return best;
}
