/*
  * Copyright (c) 2013 Benjamin Adamson
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
  * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  * IN THE SOFTWARE.
*/
#include "engine.hpp"
#include "rendering_service.hpp"
#include "input_service.hpp"
#include "loading_service.hpp"
#include <SFML\Window\Event.hpp>

engine::engine(
  void
  )
{
  static asset_io::loading_service loading_se(_rendering_service);
  const auto level = loading_se.load_level("../levels/level1.txt");
  //const auto level = loading_se.load_level("whateverbitch");
}


void
engine::execute(
  void
  )
{
  bool continue_executing(true);

  while(continue_executing) {

    const auto events = _rendering_service.get_input_events();
    _rendering_service.render();
    continue_executing = input_service::process(events);
  }
}