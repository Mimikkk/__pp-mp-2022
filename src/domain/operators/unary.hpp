#pragma once
#include "../../imports.hpp"
#include "../instance.hpp"
#include "../../utils/random.hpp"

fn apply_random(const Instance &instance, vector<usize> &base) -> vector<usize> {
  shuffle(base.begin(), base.end(), std::mt19937(std::random_device()()));
  return base;
}

fn apply_1swap(const Instance &instance, vector<usize> base) -> vector<usize> {
  let high = base.size();
  let i = rnd::integer(0lu, high - 1);
  var j = rnd::integer(0lu, high - 1);
  while (base[i] == base[j]) j = rnd::integer(0lu, high - 1);

  std::swap(base[i], base[j]);
  return base;
}

fn apply_nswap(const Instance &instance, vector<usize> base) -> vector<usize> {
  let high = base.size();

  loop {
    let i = rnd::integer(0lu, high - 1);
    var j = rnd::integer(0lu, high - 1);
    while (base[i] == base[j]) j = rnd::integer(0lu, high - 1);

    std::swap(base[i], base[j]);
    if (rnd::boolean()) break;
  }

  return base;
}
