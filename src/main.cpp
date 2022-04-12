#include "imports.hpp"
#include "domain/thread.hpp"
#include "domain/orlib_reader.hpp"
#include "utils/console.hpp"
#include "domain/operators/unary.hpp"
#include "domain/operators/binary.hpp"
#include "domain/operators/nullary.hpp"

fn main(i32 argc, byte **argv) -> i32 {
  if (argc != 2) {
    console::error("Invalid use: %s <instance file>", argv[0]);
    console::error("Instance file should be located in resources/instances directory");
    exit(1);
  }
  var filename = argv[1];

  thread::initialize();

  let path = fs::current_path() / "resources/instances" / filename;
  console::event("Reading: file '%s' at '%s'", path.filename().c_str(), path.c_str());

  let instance = OrlibReader::read(path);
  console::info("Read instance: \n%s", instance.as_string().c_str());
  console::info("UpperBound: %lu", instance.UpperBound);
  console::info("LowerBound: %lu", instance.LowerBound);

  var order = instance.create_initial_order();
  console::info("Order: %s", str(order).c_str());
  order = apply_random(instance, order);
  console::info("Order: %s", str(order).c_str());

  let candidate = instance.create_candidate(order);
  order = apply_genetic(instance, order, apply_random(instance));
  console::log("\n%s", str(candidate.Schedule).c_str());
  console::info("Makespan: %lu", candidate.Makespan);

  exit(0);
}
