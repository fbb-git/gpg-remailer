#include "main.ih"

char hexChar(std::istringstream &in)
{
    int value;
                                    // char beyond = is not a hex-char?
    if (string("0123456789abcdefABCDEF").find(in.peek()) == string::npos)
        value = '=';                // then just put out the '='
    else        
    {
        char buffer[3];

        in >> setw(sizeof(buffer)) >> buffer;

        istringstream hexConf(buffer);
        hexConf >> hex >> value;
    }

    return value;
}
        



