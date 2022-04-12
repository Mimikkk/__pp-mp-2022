#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"
#include "../../utils/random.hpp"

fn apply_genetic(const Instance &instance, const vector<usize> &first, const vector<usize> &second) -> vector<usize> {
  let length = first.size();

  vector<bool> visited_first(length, false);
  vector<bool> visited_second(length, false);

  vector<usize> result(length, 0);

  usize result_i = 0;
  usize a_i = 0;
  usize b_i = 0;

  loop {
    var add = rnd::boolean() ? first[a_i] : second[b_i];
    result[result_i] = add;
    result_i += 1;

    if (result_i >= length) return result;

    var i = a_i;
    loop {
      if (first[i] == add && !visited_first[i]) {
        visited_first[i] = true;
        break;
      }
      ++i;
    }
    while (visited_first[a_i]) ++a_i;

    i = b_i;
    loop {
      if (second[i] == add && !visited_second[i]) {
        visited_second[i] = true;
        break;
      }
      ++i;
    }
    while (visited_second[b_i]) ++b_i;
  }
}
