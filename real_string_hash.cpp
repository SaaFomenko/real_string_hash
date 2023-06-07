#include <iostream>


unsigned int real_string_hash(std::string& str, int p, int n)
{
    const char* char_str = str.c_str();
    unsigned int hash = 0;
    unsigned int i = 0;



    while (char_str[i] != 0)
    {
        unsigned int code_char = static_cast<int>(char_str[i]);

        hash += static_cast<int>(char_str[i]);
        ++i;
    }

    return hash;
}


int main(int argc, char const *argv[])
{
    
    return 0;
}
