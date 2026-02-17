#ifndef _BASE64_HPP_H
#define _BASE64_HPP_H

#include <string>
#include <vector>

const char base64_alphabet[64] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    '0','1','2','3','4','5','6','7','8','9',
    '+','/'
};

const char base64_padding = '=';

std::string base64_encode(std::vector<char>& input)
{
    std::size_t n_full_chunks = input.size() / 3;
    std::size_t n_bytes_in_last_chunk = input.size() % 3;
    std::size_t output_length = (n_full_chunks + 1) * 4;          // +1 for worst case

    std::string output;
    output.reserve(output_length);

    // full chunks
    size_t input_byte_index = 0;
    for (input_byte_index = 0; input_byte_index < n_full_chunks; input_byte_index++)
    {
        uint32_t tmp = ((uint32_t)(input[3*input_byte_index + 0]) << 16);
        tmp |= ((uint32_t)(input[3*input_byte_index + 1]) << 8);
        tmp |= ((uint32_t)(input[3*input_byte_index + 2]) << 0);

        uint8_t s1 = ((tmp >> 18) & 0x3F);
        uint8_t s2 = ((tmp >> 12) & 0x3F);
        uint8_t s3 = ((tmp >> 6) & 0x3F);
        uint8_t s4 = ((tmp >> 0) & 0x3F);

        output += base64_alphabet[s1];
        output += base64_alphabet[s2];
        output += base64_alphabet[s3];
        output += base64_alphabet[s4];
    }

    // last chunk
    if (2 ==  n_bytes_in_last_chunk)
    {
        uint32_t tmp = ((uint32_t)(input[3*input_byte_index + 0]) << 10);
        tmp |= ((uint32_t)(input[3*input_byte_index + 1]) << 2);

        uint8_t s1 = ((tmp >> 12) & 0x3F);
        uint8_t s2 = ((tmp >> 6) & 0x3F);
        uint8_t s3 = ((tmp >> 0) & 0x3F);

        output += base64_alphabet[s1];
        output += base64_alphabet[s2];
        output += base64_alphabet[s3];
        output += base64_padding;
    }
    else if (1 == n_bytes_in_last_chunk)
    {
        uint32_t tmp = ((uint32_t)(input[3*input_byte_index + 0]) << 4);

        uint8_t s1 = ((tmp >> 6) & 0x3F);
        uint8_t s2 = ((tmp >> 0) & 0x3F);

        output += base64_alphabet[s1];
        output += base64_alphabet[s2];
        output += base64_padding;
        output += base64_padding;
    }

    return output;
}

std::string base64_encode(std::string& input)
{
    std::vector<char> buffer(input.begin(), input.end());
    return base64_encode(buffer);
}

#endif
