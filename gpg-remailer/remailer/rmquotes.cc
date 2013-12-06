#include "remailer.ih"

void Remailer::rmQuotes(string &str) const
{
    size_t pos;                     // remove quotes/dquotes

    while ((pos = str.find_first_of(R"q('")q") != string::npos))
        str.erase(pos, 1);
}
