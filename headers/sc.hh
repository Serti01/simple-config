#pragma once

#include <fstream>
#include <clocale>
#include <string>
#include <cstring>
#include <cwchar>
#include <vector>
#include <regex>

namespace sc {
    enum class value_t : std::uint8_t {
        null,
        array,
        string,
        boolean,
        nint,
        nuint,
        nfloat,
        bytes
    };

    struct scdata {
        std::string name;
        value_t type;
        void *data;
    };

    class sc {
        protected:
            bool error = false;

        public:
            enum internal_state {
                none,
                comment,
                readName,
                readType,
                readValue
            };

            sc();
            std::vector<scdata> data;
            enum internal_state state = none;
            const void setError(bool e);
    };

    // Inits sc
    extern void init();

    // Reads a file, parses, and returns the output
    extern sc fread(std::string filename);
    
    // Reads a file, parses, and returns the output
    extern sc fread(wchar_t *filename);
    
    // Reads a file, parses, and returns the output
    extern sc fread(const char *filename);

    // Reads a file, parses, and returns the output
    extern sc fread(std::ifstream file);
    
    // Parses input from a stream and returns the output
    extern sc parses(std::ifstream *f);
    
}