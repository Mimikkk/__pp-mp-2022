#pragma once
#include "../imports.hpp"
#include "candidate.hpp"

class Instance {
private:
  static fn find_lower_bound(vector<vector<usize>> jobs) {
    let m = jobs.front().size() / 2;
    vector<usize> a(m, SIZE_MAX);
    vector<usize> b(m, SIZE_MAX);
    vector<usize> t(m, 0);
    usize bound = 0;

    for (let &job: jobs) {
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
    for (var i = 0; i < m; ++i) {
      result = a[i] + b[i] + t[i];
      if (result > bound) bound = result;
    }

    return bound;
  }
  static fn find_upper_bound(vector<vector<usize>> jobs) {
    usize bound = 0;

    for (let &job: jobs) {
      for (var i = 1; i < job.size(); i += 2) {
        bound += job[i];
      }
    }
    return bound;
  }

  fn create_schedule(const vector<usize> &order) const {
    var schedule = vector<vector<usize>>(M, vector<usize>(3 * N, 0));

    vector<usize> machine_state(M, 0);
    vector<usize> machine_time(M, 0);
    vector<usize> job_state(N, 0);
    vector<usize> job_time(N, 0);

    for (let &job: order) {
      var job_step = job_state[job]++ << 1;
      var machine = Jobs[job][job_step++];

      var start = std::max(machine_time[machine], job_time[job]);
      var end = start + Jobs[job][job_step];

      machine_time[machine] = end;
      job_time[job] = end;

      schedule[machine][machine_state[machine]++] = job;
      schedule[machine][machine_state[machine]++] = start;
      schedule[machine][machine_state[machine]++] = end;
    }
    return schedule;
  }
public:
  const string Name;
  const usize LowerBound;
  const usize UpperBound;
  const usize N;
  const usize M;
  const vector<vector<usize>> Jobs;

  Instance(const string &name, const vector<vector<usize>> &jobs)
    : N(jobs.size()), M(jobs.front().size() / 2),
      Name(move(name)),
      LowerBound(find_lower_bound(jobs)),
      UpperBound(find_upper_bound(jobs)),
      Jobs(move(jobs)) {}

  fn as_string() const {
    std::stringstream ss;
    ss << "Instance " << Name << ": " << N << " jobs, " << M << " machines." << std::endl;
    for (auto job: Jobs) {
      ss << "- ";
      for (auto machine: job) {
        ss << machine << " ";
      }
      ss << std::endl;
    }
    ss << "Lower bound: " << LowerBound << std::endl;
    ss << "Upper bound: " << UpperBound << std::endl;
    return ss.str();
  }

  fn create_candidate(const vector<usize> &order) const -> Candidate {
    return Candidate(order, create_schedule(order));
  }

  fn create_initial_order() const {
    vector<usize> order(N * M);
    for (usize i = 0; i < N; ++i) std::fill_n(order.begin() + (i * M), M, i);
    return order;
  }
};
