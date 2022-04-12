#include "imports.hpp"
#include "domain/thread.hpp"
#include "domain/orlib_reader.hpp"
#include "utils/console.hpp"

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
  console::info("Read instance: \n%s", instance.as_string().c_str());

  exit(0);
}
