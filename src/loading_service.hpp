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
#pragma once
#include <string>
#include <vector>
#include <utility>
#include <ExpectedT\expected.hpp>
#include "level.hpp"
//
// forward declaration
class rendering_service;
//
// namespace declarations
namespace asset_io
{
  //
  // enumeration declarations
  enum token_type {
    OPENING_BRACE = 0,
    CLOSING_BRACE,
    TEXT_IDENTIFIER,
    COLON,
    COMMA,
    OPENING_BRACKET,
    CLOSING_BRACKET
  };
  //
  // class declaration
  class loading_service
  {
    //
    // members
    rendering_service &_rendering_service;
  
    //
    // members
    std::vector<std::pair<token_type, std::string>> parse_tokens(const std::string &input) const;
    expected<std::pair<asset_io::token_type, std::string>> read_token(const std::string &input, std::string::const_iterator &it) const;
    expected<std::string> parse_until_quote_character_inclusive(const std::string &input, std::string::const_iterator &it) const;
  public:
  
    //
    // constructors
    loading_service(rendering_service &rs);
  
    //
    // methods
    data::level load_level(const std::string &level_file_name);
  };
}