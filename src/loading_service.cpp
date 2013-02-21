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
#include <string>
#include <sstream>
#include <stack>
#include <fstream>
#include <queue>
#include "level.hpp"
#include "sprite_component.hpp"
#include "loading_service.hpp"
#include "rendering_service.hpp"
#include "unexpected_end_of_file_exception.hpp"

#include <boost\log\trivial.hpp>

static const std::string ENEMY_TEXT_FILE("../assets/enemies.gif");

asset_io::loading_service::loading_service(
  rendering_service &rs
  ) : _rendering_service(rs)
{
  BOOST_LOG_TRIVIAL(trace) << "holy crap boost logging son.";
  sf::Texture texture;
  const bool loadResult = texture.loadFromFile(ENEMY_TEXT_FILE);
  if(loadResult == false) {
    //
    // ... log texture load from file error
  }
}


data::level
asset_io::loading_service::load_level(
  const std::string &level_file_name
  )
{
  std::ifstream file;
  file.open(level_file_name);
  if(file.is_open() == false) {
    //
    // log, failed to open file correctly.
    __debugbreak();
  }
  
  std::stringstream buffer;
  buffer << file.rdbuf();
  const auto tokens = parse_tokens(buffer.str());

  const auto first_token = tokens.front();


  data::level loaded_level;
  data::sprite_component sprite_component;


  sf::IntRect bounds(0, 0, 32, 48);
  sprite_component.sprite.setTextureRect(bounds);
  sprite_component.sprite.move(100, 300);

  data::entity entity;
  _rendering_service.add_entity(entity, std::move(sprite_component));
  loaded_level.entities.emplace_back(std::move(entity));

  return loaded_level;
}


std::vector<std::pair<asset_io::token_type, std::string>>
asset_io::loading_service::parse_tokens(
  const std::string &input
  ) const
{
  std::vector<std::pair<asset_io::token_type, std::string>> result;

  auto it = input.cbegin();

  while(it != input.cend()) {

    const auto token = read_token(input, it);
    if(token.valid() == false) {
      //
      // log an error, invalid data in file.
      result.clear();
      return result;
    }

    result.emplace_back( token.get() );
  }

   return result;
}


expected<std::pair<asset_io::token_type, std::string>>
asset_io::loading_service::read_token(
  const std::string &input,
  std::string::const_iterator &it
  ) const
{
  std::pair<token_type, std::string> result;
  std::map<std::string, token_type> char_to_token_map;
  char_to_token_map.emplace("\"", TEXT_IDENTIFIER);
  char_to_token_map.emplace("{", OPENING_BRACE);
  char_to_token_map.emplace("}", CLOSING_BRACE);
  char_to_token_map.emplace(":", COLON);
  char_to_token_map.emplace(",", COMMA);
  char_to_token_map.emplace("[", OPENING_BRACKET);
  char_to_token_map.emplace("]", CLOSING_BRACKET);

  while(it != input.cend()) {

    result.second += *it;
    ++it;

    const bool token_found = char_to_token_map.find(result.second) == char_to_token_map.cend();
    if(token_found == false || result.second == "\"") {
      const auto parse_result = parse_until_quote_character_inclusive(input, it);

      if(parse_result.valid() == true) {
        result.second += parse_result.get();
      }
      else {
        result.second = parse_result.hasException<assetio::unexpected_end_of_file_exception>();
      }
    }

    }

    switch(result.second.back()) {

    case '"':
      result.first = TEXT_IDENTIFIER;
      //result.second += parse_until_quote_character_inclusive(input, it);
      return result;

    case '{':
      result.first = OPENING_BRACE;
      return result;

    case '}':
      result.first = CLOSING_BRACE;
      return result;

    case ':':
      result.first = COLON;
      return result;

    case ',':
      result.first = COMMA;
      return result;

    case '[':
      result.first = OPENING_BRACKET;
      return result;

    case ']':
      result.first = CLOSING_BRACKET;
      return result;
    }
  //}

  return result;
}


expected<std::string>
asset_io::loading_service::parse_until_quote_character_inclusive(
  const std::string &input,
  std::string::const_iterator &it
  ) const
{
  std::string result;

  while(it != input.cend()) {

    result += *it;
    ++it;

    if(it != input.cend()) {
      return expected<std::string>::fromException( assetio::unexpected_end_of_file_exception() );
    }

    if(result.back() == '"') {
      break;
    }
  }

  return result;
}