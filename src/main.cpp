#include "imports.hpp"
#include "domain/thread.hpp"
#include "domain/orlib_reader.hpp"
#include "utils/console.hpp"
#include "domain/operators/nullary.hpp"
#include "domain/heuristics/random_sample.hpp"
#include "utils/color.hpp"
#include "domain/heuristics/hill_climber.hpp"

fn main(i32 argc, byte **argv) -> i32 {
  if (argc != 2) {
    console::error("Invalid use: %s <instance file>", argv[0]);
    console::error("Instance file should be located in resources/instances directory");
    exit(1);
  }
  var filename = argv[1];

  thread::initialize();

  let path = fs::current_path() / "resources/instances" / filename;
  console::info("Reading: file '%s' at '%s'", path.filename().c_str(), path.c_str());

  let instance = OrlibReader::read(path);
  console::info("Read instance: \n%s", instance.as_string().c_str());


  var best = instance.create_candidate(instance.create_initial_order());
  var best_id = 0;

  #pragma omp parallel default(shared)
  {
    let candidate = hill_climber(instance, 1000000, 1676);
    console::info("\n%s", str(candidate.Schedule).c_str());
    console::info("Makespan: %s%lu", color::Silver, candidate.Makespan);

    #pragma omp critical
    {
      if (candidate > best) {
        best = move(candidate);
        best_id = thread::ID;
        console::event("Has better candidate than %s%d: %lu", color::dynamic(best_id).get(), best_id, best.Makespan);
      }
    }
  }

  console::info("Read instance: \n%s", instance.as_string().c_str());
  console::event("\n%s", str(best.Schedule).c_str());
  console::event("Best candidate: %s%lu made by %s%02d",
                 color::Silver, best.Makespan, color::dynamic(best_id).get(), best_id);

  exit(0);
}
