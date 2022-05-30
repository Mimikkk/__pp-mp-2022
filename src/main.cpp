#ifndef cuda
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
    exit(1);
  }
  var filename = argv[1];

  thread::initialize();

  var path = fs::current_path() / "resources/instances" / filename;
  console::info("Reading: file '%s' at '%s'", path.filename().c_str(), path.c_str());

  let instance = OrlibReader::read(path);
  console::info("Read instance: \n%s", instance.as_string().c_str());

  var best_id = 0;
  let best = random_sample_threaded(instance, 1, &best_id);

  console::info("Read instance: \n%s", instance.as_string().c_str());
  console::event("\n%s", str(best.Schedule).c_str());
  console::event("Best candidate: %s%lu %smade by %s%02d",
                 color::Silver, best.Makespan, color::Green, color::dynamic(best_id).get(), best_id);

  path = fs::current_path() / "solutions/random_sample" / str("mp_%d_%s.json", best.Makespan, instance.Name.c_str()).get();

  CandidateWriter::write(path, instance, best);
}
#endif
