// All source files share a common LICENSE, please see the license under the LICENSE file in the
// root directory of this repository.
//
// This program demonstrates the 
#include <libshort/libshort.hpp>
#include <libshort/modules/defaults/sfml.hpp>
#include <astrogame/modules/main.hpp>

int
main(int arc, char **argv)
{
  namespace sh = libshort;
  auto env = sh::parse_args(argc, argv)
    .on_error("Error loading config, reason '%s'");

  auto os = sh::os::detect_current::make(env)
    .on_error("Error loading OS, reason '%s'");

  auto loop = sh::loop_builder()
    .libs()
    .gfx(sh::modules::default::make_sfml())
    .audio(sh::modules::default::make_libaudio())
    .input(sh::modules::default::make_sfml())
    .build(env)
    .ignore_errors(); // Useful for testing, or not.

  // Shortcut provided by the library.
  auto loop2 = sh::loop_builder(sh::default_modules::sfml_and_libaudio())
    .build(env)
    .ignore_errors();

  // You can also build loops by handl
  auto loop3 = sh::loop_builder()
    .libs()
    .gfx([](auto &os) {
        os.ostream() << "Hi from here. Our job is to return a lib object representing our gfx lib.";
        return sh::lib_loader(os, env);})
    .audio(sh::modules::test::make_noop())
    .input(sh::modules::test::make_automated())
    .build(env).
    on_error("Error building loop, reason '%s'"); // Version taking a lambda also available.

  auto game = AstroGame::load_game(config, os)
    .on_error("Error loading game from config, reason '%s'");
  auto game = sh::game_builder()
    .allocators(AstroGame::allocators())
    .config(AstroGame::config())
    .build(loop, game)
    // .build(loop2, game)
    // or
    // .build(loop3, game)
    .on_error("Unexpected error during runtime '%s'");
  return game.run();
}
