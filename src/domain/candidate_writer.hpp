#pragma once
#include "../imports.hpp"
#include "./instance.hpp"

class CandidateWriter {
public:
  static fn write(const fs::path& path, const Instance& instance, const Candidate& candidate) {
    let json = str("{\n"
                   "  \"info\": {\n"
                   "    \"name\": \"%s\",\n"
                   "    \"instance\": {\n"
                   "      \"job_count\": %d,\n"
                   "      \"machine_count\": %d\n"
                   "    }\n"
                   "  },\n"
                   "  \"solution\": {\n"
                   "    \"makespan\": %d,\n"
                   "    \"schedule\": %s\n"
                   "  }\n"
                   "}",
                   path.filename().c_str(),
                   instance.M, instance.N,
                   candidate.Makespan, str(candidate.Schedule).c_str());

    std::ofstream file(path);
    file << json.get();
    file.close();
  }
};
