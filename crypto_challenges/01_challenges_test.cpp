#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "base64.hpp"

std::vector<char> hex_string_to_bytes(const std::string& input)
{
    assert(0 == (input.length() % 2));
    const std::size_t expected_len = input.length() / 2;
    std::vector<char> output;
    output.reserve(expected_len);

    for (size_t i = 0; i < input.length(); i += 2)
    {
        unsigned char val = std::stoi(input.substr(i, 2), nullptr, 16);
        output.push_back(val);
    }

    return output;
}


TEST(challenge_01, BasicAssertions) 
{
  std::string input_1("Many hands make light work.");
  std::string actual_output_1 = base64_encode(input_1);
  std::string expected_output_1("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
  EXPECT_EQ(expected_output_1, actual_output_1);
  
  std::string input_2("Man");
  std::string actual_output_2 = base64_encode(input_2);
  std::string expected_output_2("TWFu");
  EXPECT_EQ(expected_output_2, actual_output_2);
  
  std::string input_3("Ma");
  std::string actual_output_3 = base64_encode(input_3);
  std::string expected_output_3("TWE=");
  EXPECT_EQ(expected_output_3, actual_output_3);

  std::string input_4("M");
  std::string actual_output_4 = base64_encode(input_4);
  std::string expected_output_4("TQ==");
  EXPECT_EQ(expected_output_4, actual_output_4);

  std::string input_5_hex_str("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
  std::vector<char> input_5(hex_string_to_bytes(input_5_hex_str));
  std::string actual_output_5 = base64_encode(input_5);
  std::string expected_output_5("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
  EXPECT_EQ(expected_output_5, actual_output_5);
}

//49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
