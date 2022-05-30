#pragma once
#include "../imports.hpp"

namespace rnd {
  namespace {
    inline fn generator() -> std::mt19937 {
      static std::random_device device;
      static std::mt19937 gen(device());
      return gen;
    }
  }

  template<typename T = i32>
  inline fn create_i_uniform(T min, T max) {
    return std::uniform_int_distribution<T>(min, max);
  }

  template<typename T = f32>
  inline fn create_f_uniform(T min, T max) {
    return std::uniform_real_distribution<T>(min, max);
  }

  inline fn create_b_uniform(f64 p) {
    return std::bernoulli_distribution(p);
  }

  template<typename T = f32>
  inline fn real(T min = 0.0, T max = 1.0) {
    static var uniform = create_f_uniform<T>(min, max);
    static var gen = generator();
    return uniform(gen);
  }

  template<typename T = i32>
  inline fn integer(T min = 0, T max = 1) {
    static var uniform = create_i_uniform<T>(min, max);
    static var gen = generator();
    return uniform(gen);
  }

  inline fn boolean(f64 limit = 0.5) {
    static var uniform = create_b_uniform(limit);
    static var gen = generator();
    return uniform(gen);
  }
}
