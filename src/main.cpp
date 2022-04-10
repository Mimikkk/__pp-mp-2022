#include "imports.hpp"
#include "utils/console.hpp"

fn main() -> i32 {
  #pragma omp parallel default(none)
  {
    console::log("Hello, world");
    console::info("Hello, world");
    console::error("Hello, world");
    console::event("Hello, world");
  }
  return 0;
}
