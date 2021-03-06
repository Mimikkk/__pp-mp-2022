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
  fn operator==(const Candidate& other) const { return Order == other.Order; }
  fn operator>(const Candidate& other) const { return Makespan < other.Makespan; }
  fn operator<(const Candidate& other) const { return Makespan > other.Makespan; }

  Candidate(const vector<usize> &order, const vector<vector<usize>> &schedule)
    : Makespan(find_makespan(schedule)), Order(order), Schedule(schedule) {}

  usize Makespan;
  vector<usize> Order;
  vector<vector<usize>> Schedule;
};
