#pragma once
#include "../imports.hpp"
#include "instance.hpp"
#include "../utils/console.hpp"

fn create_schedule(const Instance &instance, const vector<usize> &order) {
  var schedule = vector<vector<usize>>(instance.M, vector<usize>(3 * instance.N, 0));
  console::log("M, 3*N: %lu %lu", schedule.size(), schedule[0].size());

  vector<usize> machine_state(instance.M, 0);
  vector<usize> machine_time(instance.M, 0);
  vector<usize> job_state(instance.N, 0);
  vector<usize> job_time(instance.N, 0);

  for (const auto &job: order) {
    console::log("Job: %lu", job);
    var job_step = job_state[job] * 2;
    console::log("JobStep: %lu", job_step);
    var machine = instance.Jobs[job_step][job];
    console::log("Machine: %lu", machine);
    job_state[job] += 1;

    console::log("MachineTime: %lu", machine_time[machine]);
    console::log("JobTime: %lu", job_time[job]);

    var start = std::max(machine_time[machine], job_time[job]);
    console::log("Start: %lu", start);
    var end = start + instance.Jobs[job][++job_step];
    console::log("End: %lu", end);

    machine_time[machine] = end;
    console::log("MachineTime: %lu", job);
    job_time[job] = end;
    console::log("JobTime: %lu", job);

    console::log("Machine State: %lu %lu", machine, machine_state[machine]);
    schedule[machine][machine_state[machine]] = job;
    console::log("1: %lu", job);
    schedule[machine][machine_state[machine] + 1] = start;
    console::log("2: %lu", job);
    schedule[machine][machine_state[machine] + 2] = end;
    machine_state[machine] += 3;
    console::log("3: %lu", job);
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

fn find_lower_bound(Instance instance) {
  vector<usize> a(instance.M, SIZE_MAX);
  vector<usize> b(instance.M, SIZE_MAX);
  vector<usize> t(instance.M, 0);
  usize bound = 0;

  for (var i = instance.N - 1; i >= 0; ++i) {
    let job = instance.Jobs[i];

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

fn find_upper_bound(Instance instance) {
  usize bound = 0;
  for (const auto &job: instance.Jobs) {
    for (var i = 1; i < job.size(); i += 2) {
      bound += job[i];
    }
  }
  return bound;
}

fn create_candidate(Instance instance, vector<usize> order) -> Candidate {
  let schedule = create_schedule(instance, order);
  let makespan = find_makespan(schedule);

  return {makespan, order, schedule};
}

fn create_order(Instance instance) {
  vector<usize> order(instance.N * instance.M);
  for (usize i = 0; i < instance.N; ++i) std::fill_n(order.begin() + (i * instance.M), instance.M, i);
  return order;
}

fn shuffle_order(vector<usize> order) -> vector<usize> {
  std::shuffle(order.begin(), order.end(), std::mt19937(std::random_device()()));
  return order;
}