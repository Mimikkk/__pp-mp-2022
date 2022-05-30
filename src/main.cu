#ifdef cuda
#include "imports.hpp"
#include "domain/thread.hpp"
#include "domain/orlib_reader.hpp"
#include "domain/candidate_writer.hpp"
#include "utils/console.hpp"
#include "domain/operators/nullary.hpp"
#include "domain/heuristics/random_sample.hpp"
#include "utils/color.hpp"
#include "domain/heuristics/hill_climber.hpp"

fn main(i32 argc, byte **argv) -> i32 {
  if (argc != 2) {
    console::error("Invalid use: %s <instance file>", argv[0]);
    console::error("Instance file should be located in resources/instances directory");
  }
  var filename = argv[1];

  var path = fs::current_path() / "resources/instances" / filename;
  console::info("Reading: file '%s' at '%s'", path.filename().c_str(), path.c_str());

  let instance = OrlibReader::read(path);
  console::info("Read instance: \n%s", instance.as_string().c_str());

  let best = random_sample(instance, 1);

  console::info("Read instance: \n%s", instance.as_string().c_str());
  console::event("\n%s", str(best.Schedule).c_str());
  console::event("Best candidate: %s%lu", color::Silver, best.Makespan, color::Green);

  path = fs::current_path() / "solutions/random_sample" / str("cuda_%d_%s.json", best.Makespan, instance.Name.c_str()).get();
  CandidateWriter::write(path, instance, best);
}
#endif
