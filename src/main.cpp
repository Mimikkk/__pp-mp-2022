#include "imports.hpp"
#include "utils/console.hpp"
#include "domain/thread.hpp"

fn main() -> i32 {
  thread::initialize();

  #pragma omp parallel default(none)
  {
    console::log("Hello from thread %d", thread::ID);
    console::event("Hello from thread %d", thread::ID);
    console::info("Hello from thread %d", thread::ID);
    console::error("Hello from thread %d", thread::ID);
  }

  return 0;
}
