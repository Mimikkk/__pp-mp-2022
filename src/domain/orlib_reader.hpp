#pragma once
#include "../imports.hpp"
#include "./instance.hpp"

class OrlibReader {
public:
  static fn read(fs::path path) -> Instance {
    if (not is_regular_file(path)) throw std::domain_error("Not a file");
    return Instance(path.stem().string(), read_jobs(path));
  }
private:
  static fn read_jobs(fs::path path) -> vector<vector<usize>> {
    std::ifstream infile(path);
    usize n, m;
    infile >> n >> m;
    vector<vector<usize>> jobs(m, vector<usize>(n));
    for (var i = 0; i < m; i++) for (var j = 0; j < n; j++) infile >> jobs[i][j];
    return jobs;
  }
};
