#include "sc.hh"
#include <regex>

void init() {
    std::setlocale(LC_ALL, "");
}

sc::sc::sc() {

}

sc::sc sc::fread(std::string filename) {
    std::ifstream f(filename);
    
    return parses(&f);
}

sc::sc sc::fread(wchar_t *filename) {
    std::mbstate_t state = std::mbstate_t();
    std::vector<char> mbstr(std::wcslen(filename));
    std::wcsrtombs(&mbstr[0], (const wchar_t**)&filename, mbstr.size(), &state);
    
    std::ifstream f(&mbstr[0]);

    return parses(&f);
}

sc::sc sc::fread(const char *filename) {
    std::ifstream f(filename);

    return parses(&f);
}

sc::sc sc::fread(std::ifstream file) {
    return parses(&file);
}

bool testChar(char c) {
    if (c == ' ' || c == '\t' || c == '\n')
        return false;
    
    return true;
}

const void sc::sc::setError(bool e) {
    this->error = e;
}

sc::sc sc::parses(std::ifstream *f) {
    sc data;
    struct scdata tmp;

    char buf;
    char lbuf;

    #define setErrorandReturn() data.setError(true); return data

    while (!f->eof()) {
        f->get(buf);

        // idk if this is a good solution or not
        if (buf == '\0') break;
        // printf("%i, %llu, %i\n", f->eof(), (unsigned long long)f->tellg(), data.state);

        switch (data.state) {
            case sc::none: {
                // if buffer is whitespace, skip to the next character
                if (!testChar(buf))
                    break;
                // if buffer is '//' treat it as a comment and disregard the rest of the line
                else if (buf == '/') {
                    // test if comment
                    f->get(buf);
                    if (buf == '/') {
                        data.state = sc::comment;
                        break;
                    }
                    else {
                        printf("libsc: Error parsing file: '/' is invalid in this context\n");
                        setErrorandReturn();
                    }
                } else data.state = sc::readName;

                break;
            }
            case sc::comment: {
                // keep skipping over characters until new line
                while (f->get(buf),buf != '\n' && !f->eof());
                
                data.state = sc::none;
                break;
            }
            case sc::readName: {
                // read name into data name, change state on '/'
                if (!testChar(buf)) {
                    printf("libsc: Error parsing property name: Whitespace and newlines not allowed in this context\n");
                    setErrorandReturn();
                } else if (f->eof()) {
                    printf("libsc: Error parsing property name: Unexpected EOF\n");
                    setErrorandReturn();
                }

                f->seekg((unsigned long long)f->tellg() - 2);

                while (f->get(buf),buf != '/') {
                    tmp.name += buf;
                    if (f->eof()) {
                        printf("libsc: Error parsing property name: Unexpected EOF\n");
                        setErrorandReturn();
                    }
                }
                data.state = sc::readType;

                break;
            }
            case sc::readType: {
                // read type and fail on invalid type, read into data and change state on ':'
                if (!testChar(buf)) {
                    printf("libsc: Error parsing property type: Whitespace and newlines not allowed in this context\n");
                    setErrorandReturn();
                } else if (f->eof()) {
                    printf("libsc: Error parsing property type: Unexpected EOF\n");
                    setErrorandReturn();
                }

                std::string type_s;
                while ((buf != ':' || !testChar(buf)) && type_s != "null") {
                    type_s += buf;
                    f->get(buf);
                    if (f->eof()) {
                        printf("libsc: Error parsing property type: Unexpected EOF\n");
                        setErrorandReturn();
                    }
                }

                if (type_s == "null") {
                    f->seekg((unsigned long long)f->tellg() - 1);
                }

                enum value_t type = (enum value_t)8;
                #define checkType(etype, str) if (std::regex_match(type_s.c_str(), std::regex(str))) type = (enum value_t)etype

                // parse type
                checkType(0, "null");
                checkType(1, "array\\[(.*)\\]");
                checkType(2, "string");
                checkType(3, "boolean");
                checkType(4, "int");
                checkType(5, "uint");
                checkType(6, "float");
                checkType(7, "bytes");

                if ((int)type == 8) {
                    printf("libsc: Error parsing property type: Unrecognized type \"%s\"\n", type_s.c_str());
                    setErrorandReturn();
                } 

                tmp.type = type;

                data.state = sc::readValue;

                break;
            }
            case sc::readValue: {
                // read value, fail on invalid value, read into data and change state on ';'
                
                // before any value, ignore whitespace
                while (!testChar(buf)) {
                    f->get(buf);
                    if (f->eof()) {
                        printf("libsc: Error while parsing value: Unexpected EOF\n");
                        setErrorandReturn();
                    }
                }

                std::string value;

                // read until ;
                while (buf != ';') {
                    value += buf;
                    f->get(buf);
                    if (f->eof()) {
                        printf("libsc: Error while parsing value: Unexpected EOF\n");
                        setErrorandReturn();
                    }
                }

                char *tmpv;
                tmpv = (char *)malloc(value.length());

                switch (tmp.type) {
                    case value_t::null:
                        tmp.data = nullptr;
                        break;
                    case value_t::array: // ill make you later

                        break;
                    case value_t::string:
                        if (value[0] != '"' || value[value.length()-1] != '"') {
                            printf("libsc: Error parsing property value: String type doesnt contain \"'s\n");
                            setErrorandReturn();
                        }
                        value.copy(tmpv, value.length()-1, 1);
                        value = tmpv;
                        value[value.length()-1] = '\0';
                        break;
                    case value_t::boolean:
                        if (std::regex_match(value, std::regex("true"))) {
                            tmp.data = new bool(true);
                        } else if (std::regex_match(value, std::regex("false"))) {
                            tmp.data = new bool(false);
                        } else {
                            printf("libsc: Error parsing property value: \"%s\" isnt a valid boolean value\n", value.c_str());
                            setErrorandReturn();
                        }
                        printf("%i\n", *(bool *)tmp.data);
                        break;
                        // very tired, its in a relatively working state
                    case value_t::nint:
                        break;
                    case value_t::nuint:
                        break;
                    case value_t::nfloat:
                        break;
                    case value_t::bytes:
                        break;
                    default:
                        break;
                }

                free(tmpv);

                data.state = sc::none;

                data.data.push_back(tmp);
                tmp = *(new scdata);

                break;
            }
            default:
                break;
        }

        lbuf = buf;
    }

    for (auto &d : data.data) {
        printf("%s\n", d.name.c_str());
    }

    return data;
}