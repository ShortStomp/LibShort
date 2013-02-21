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
#include <SFML\Window\Event.hpp>
#include "input_service.hpp"

bool
input_service::priv::process_single_event(
  const sf::Event &event
  )
{
  bool result = true;

  switch(event.type) {

  case sf::Event::KeyPressed:
    result = process_keyboard_event(event.key);
    break;

  case sf::Event::Closed:
    result = false;
    break;

  }

  return result;
}


bool
input_service::priv::process_keyboard_event(
  const sf::Event::KeyEvent &key_event
  )
{
  bool result = true;

  switch(key_event.code) {

  case sf::Keyboard::Escape:
    result = false;
    break;

  }

  return result;
}


bool
input_service::process(
  const std::vector<sf::Event> &events
  )
{
  bool result = true;

  for(const auto &event : events) {
    result = priv::process_single_event(event);
    if(result == false) {
      break;
    }
  }

  return result;
}