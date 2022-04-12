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

fn find_lower_bound(const Instance &instance) {
  vector<usize> a(instance.M, SIZE_MAX);
  vector<usize> b(instance.M, SIZE_MAX);
  vector<usize> t(instance.M, 0);
  usize bound = 0;

  for (let &job: instance.Jobs) {
    var job_total_time = 0;
    for (var j = 1; j < job.size(); j += 2) job_total_time += job[j];
    if (job_total_time > bound) bound = job_total_time;

    usize time;
    usize machine;
    usize job_current_time = 0;

    for (var k = 0; k < job.size(); k += 2) {
      machine = job[k];
      time = job[k + 1];
      a[machine] = std::min(a[machine], job_current_time);
      t[machine] += time;
      job_current_time += time;
      b[machine] = std::min(b[machine], job_total_time - job_current_time);
    }
  }

  usize result;
  for (var i = 0; i < instance.M; ++i) {
    result = a[i] + b[i] + t[i];
    if (result > bound) bound = result;
  }

  return bound;
}

fn find_upper_bound(const Instance &instance) {
  usize bound = 0;
  
  for (let &job: instance.Jobs) {
    for (var i = 1; i < job.size(); i += 2) {
      bound += job[i];
    }
  }
  return bound;
}

fn create_schedule(const Instance &instance, const vector<usize> &order) {
  var schedule = vector<vector<usize>>(instance.M, vector<usize>(3 * instance.N, 0));
  console::log("M, 3*N: %lu %lu", schedule.size(), schedule[0].size());

  vector<usize> machine_state(instance.M, 0);
  vector<usize> machine_time(instance.M, 0);
  vector<usize> job_state(instance.N, 0);
  vector<usize> job_time(instance.N, 0);

  for (const auto &job: order) {
    var job_step = job_state[job]++ << 1;
    var machine = instance.Jobs[job][job_step++];

    var start = std::max(machine_time[machine], job_time[job]);
    var end = start + instance.Jobs[job][job_step];

    machine_time[machine] = end;
    job_time[job] = end;

    schedule[machine][machine_state[machine]++] = job;
    schedule[machine][machine_state[machine]++] = start;
    schedule[machine][machine_state[machine]++] = end;
  }
  return schedule;
}

fn create_candidate(const Instance &instance, const vector<usize> &order) -> Candidate {
  let schedule = create_schedule(instance, order);
  let makespan = find_makespan(schedule);

  return {makespan, order, schedule};
}

fn create_order(const Instance &instance) {
  vector<usize> order(instance.N * instance.M);
  for (usize i = 0; i < instance.N; ++i) std::fill_n(order.begin() + (i * instance.M), instance.M, i);
  return order;
}

fn shuffle_order(vector<usize> order) {
  std::shuffle(order.begin(), order.end(), std::mt19937(std::random_device()()));
}
