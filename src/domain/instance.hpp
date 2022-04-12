#pragma once
#include "../imports.hpp"

class Instance {
private:
public:
  const string Name;
  const usize N;
  const usize M;
  const vector<vector<usize>> Jobs;
  Instance(const string &name, const vector<vector<usize>> &jobs)
    : N(jobs.size()), M(jobs.front().size() / 2), Jobs(move(jobs)), Name(move(name)) {}

  fn as_string() {
    std::stringstream ss;
    ss << "Instance " << Name << ": " << N << " jobs, " << M << " machines." << std::endl;
    for (auto job: Jobs) {
      ss << "- ";
      for (auto machine: job) {
        ss << machine << " ";
      }
      ss << std::endl;
    }
    return ss.str();
  }
};

