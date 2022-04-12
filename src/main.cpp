#include "imports.hpp"
#include "domain/thread.hpp"
#include "domain/orlib_reader.hpp"
#include "utils/console.hpp"
#include "domain/candidate.hpp"

string str(vector<usize> order) {
  var begin = order.begin();
  let end = order.end();

  std::stringstream ss;
  ss << '[' << *begin;
  for (++begin; begin != end; ++begin) ss << ", " << *begin;
  ss << ']';
  return ss.str();
}
string str(vector<vector<usize>> schedule) {
  var begin = schedule.begin();
  let end = schedule.end();

  std::stringstream ss;
  ss << '[' << str(*begin);
  for (++begin; begin != end; ++begin) ss << ",\n " << str(*begin);
  ss << ']';
  return ss.str();
}

fn main(i32 argc, byte **argv) -> i32 {
  if (argc < 2) {
    console::error("Invalid use: %s <instance file>", argv[0]);
    console::error("Instance file should be located in resources/instances directory");
    exit(1);
  }

  thread::initialize();

  var filename = argv[1];
  var path = fs::current_path() / "resources/instances" / filename;
  console::event("Reading: file '%s' at '%s'", path.filename().c_str(), path.c_str());

  var instance = OrlibReader::read(path);
  console::info("Kurwa?? \n%s", str(instance.Jobs).c_str());
  console::info("Read instance: \n%s", instance.as_string().c_str());

  let order = create_order(instance);
  console::info("Order: %s", str(order).c_str());
  let schedule = create_schedule(instance, order);
  console::info("Order: %s", str(order).c_str());
  console::info("Makespan: %lu", find_makespan(schedule));
  console::info("Makespan: %lu", find_makespan(schedule));
  console::info("Makespan: %lu", find_makespan(schedule));

  exit(0);
}
