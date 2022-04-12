#pragma once
#include "../imports.hpp"
#include "instance.hpp"
#include "../utils/console.hpp"

class Candidate {
private:
  static fn find_makespan(const vector<vector<usize>> &schedule) {
    usize makespan = 0;
    for (let machine: schedule) {
      if (machine.back() > makespan) makespan = machine.back();
    }
    return makespan;
  }
public:
  fn operator==(Candidate other) { return Order == other.Order; }
  fn operator>(Candidate other) { return Makespan > other.Makespan; }
  fn operator<(Candidate other) { return Makespan < other.Makespan; }

  Candidate(const vector<usize> &order, const vector<vector<usize>> &schedule)
    : Makespan(find_makespan(schedule)), Order(move(order)), Schedule(move(schedule)) {}

  const usize Makespan;
  const vector<usize> Order;
  const vector<vector<usize>> Schedule;
};
