#include "../../imports.hpp"
#include "../instance.hpp"

fn cuda_random_sample(const Instance &instance, f64 time) -> Candidate {
    vector<usize> order = {};
    vector<vector<usize>> schedule = {};
    return Candidate(order, schedule);
}
