#pragma once
#include "../imports.hpp"

class Instance {
public:
  string Name;
  usize N;
  usize M;
  vector <vector<usize>> Jobs;
  Instance(string name, vector <vector<usize>> jobs) {
    Jobs = jobs;
    Name = name;
    N = jobs.size();
    M = jobs.front().size() / 2;
  }

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
