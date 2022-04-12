#pragma once
#include "../imports.hpp"
#include "instance.hpp"

fn create_schedule(const Instance &instance, const vector<usize> &order) {
  var schedule = vector<vector<usize>>(instance.M, vector<usize>(3 * instance.N, 0));

  vector<usize> machine_state(instance.M, 0);
  vector<usize> machine_time(instance.M, 0);
  vector<usize> job_state(instance.N, 0);
  vector<usize> job_time(instance.N, 0);

  for (const auto &job: order) {
    var job_step = job_state[job] << 1;
    var machine = instance.Jobs[job_step][job];
    ++job_state[job];
    var start = std::max(machine_time[machine], job_time[job]);
    var end = start + instance.Jobs[job][job_step + 1];
    machine_time[machine] = end;
    job_time[job] = end;

    schedule[machine][machine_state[machine]++] = job;
    schedule[machine][machine_state[machine]++] = start;
    schedule[machine][machine_state[machine]++] = end;
  }
  return schedule;
}

class Candidate {
public:
  fn operator==(Candidate other) { return Order == other.Order; }
  fn operator>(Candidate other) { return Makespan > other.Makespan; }
  fn operator<(Candidate other) { return Makespan < other.Makespan; }

  usize Makespan;
  vector<usize> Order;
  vector<vector<usize>> Schedule;
};

fn find_makespan(vector<vector<usize>> schedule) {
  usize makespan = 0;
  for (auto machine: schedule) {
    if (machine.back() < makespan) makespan = machine.back();
  }
  return makespan;
}

fn create_candidate(Instance instance, vector<usize> order) -> Candidate {
  let schedule = create_schedule(instance, order);
  let makespan = find_makespan(schedule);

  return {makespan, order, schedule};
}