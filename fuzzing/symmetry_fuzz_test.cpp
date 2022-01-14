#include <iostream>
#include <fstream>
#include <sstream>

#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>

int main(int argc, char **argv)
{
    if (2 > argc) {
        std::cout << "usage: " << argv[0] << " PAYLOAD\n";
        return 1;
    }

    std::ifstream payload_stream(argv[1], std::ios::binary);
    if (!payload_stream.is_open()) {
        std::cerr << "failed to open file \"" << argv[1] << "\"\n";
        return 2;
    }

    auto begin = std::istreambuf_iterator<char>(payload_stream);
    auto end = std::istreambuf_iterator<char>();

    std::string o_string(begin, end);
    std::ostringstream os;
    {
        cereal::BinaryOutputArchive oar(os);
        oar(o_string);
    }

    std::string i_string;
    std::istringstream is(os.str());
    {
        cereal::BinaryInputArchive iar(is);
        iar(i_string);
    }

    if (i_string != o_string) abort();

    return 0;
}
