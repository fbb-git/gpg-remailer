#include "mail.ih"

void Mail::hexChar(ostream &out, istream &in)
{
    int value;
                                    // char beyond = is not a hex-char?
    if (string("0123456789abcdefABCDEF").find(in.peek()) == string::npos)
    {
        out << '=';                // then just put out the '='
        return;
    }

    char buffer[3];

    in >> setw(sizeof(buffer)) >> buffer;

    istringstream hexConf(buffer);
    hexConf >> hex >> value;

    if (hexConf.tellg() != 2 || !isprint(value))
        out << '=' << buffer;
    else
        out << static_cast<char>(value);
}
