#include "main.ih"

void hexChar(std::istringstream &in)
{
    int value;
                                    // char beyond = is not a hex-char?
    if (string("0123456789abcdefABCDEF").find(in.peek()) == string::npos)
    {
        cout << '=';                // then just put out the '='
        return;
    }

    char buffer[3];

    in >> setw(sizeof(buffer)) >> buffer;

    istringstream hexConf(buffer);
    hexConf >> hex >> value;

    if (hexConf.tellg() != 2 || !isprint(value))
        cout << '=' << buffer;
    else
        cout << static_cast<char>(value);
}
