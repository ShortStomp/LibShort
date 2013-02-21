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
#include <vector>
#include "entity.hpp"
#include "rendering_service.hpp"

rendering_service::rendering_service(
  void
  )
{
  _window.create(sf::VideoMode::VideoMode(1024, 768), "LibShort");

  //
  // _sprites can not resize itself during the application
  // otherwise all the entities which hold references
  // will be invalid. this reserved amount must be static throughout the application runtime.
  // TODO: make this number a symbolic constant.
  _sprites.reserve(10000);
}


void
rendering_service::render(
  void
  )
{
  //
  // start by clearing the window
  _window.clear();

  //
  // draw each of the sprites
  for(auto sprite : _sprites) {
    _window.draw(sprite.sprite);
  }

  //
  // display the window
  _window.display();
}


std::vector<sf::Event>
rendering_service::get_input_events(
  void
  )
{
  std::vector<sf::Event> result;

  sf::Event event;
  while(_window.pollEvent(event)) {
    //
    // explicitely copy the event into the vector
    result.push_back(event);
  }

  return result;
}


bool
rendering_service::add_entity(
  data::entity &entity,
  const data::sprite_component &&component
  )
{
  _sprites.emplace_back(component);
  entity.components.emplace_back( _sprites.back() );

  //
  // success
  return true;
}