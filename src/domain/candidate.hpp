#pragma once
#include "../imports.hpp"
#include "instance.hpp"
#include "../utils/console.hpp"

class Candidate {
public:
  fn operator==(Candidate other) { return Order == other.Order; }
  fn operator>(Candidate other) { return Makespan > other.Makespan; }
  fn operator<(Candidate other) { return Makespan < other.Makespan; }

  usize Makespan;
  vector<usize> Order;
  vector<vector<usize>> Schedule;
};

fn find_makespan(const vector<vector<usize>> &schedule) {
  usize makespan = 0;
  for (let machine: schedule) {
    if (machine.back() > makespan) makespan = machine.back();
  }
  return makespan;
}

fn shuffle_order(vector<usize> order) {
  std::shuffle(order.begin(), order.end(), std::mt19937(std::random_device()()));
}
