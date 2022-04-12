#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"

fn apply_random(const Instance &instance) -> vector<usize> {
  var order = instance.create_initial_order();
  shuffle(order.begin(), order.end(), std::mt19937(std::random_device()()));
  return order;
}
