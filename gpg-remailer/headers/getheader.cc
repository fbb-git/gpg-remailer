#include "headers.ih"

string Headers::getHeader(char const *hdr)
{
    string ret;
        
    auto begin = mailHeader(hdr);
    if (begin != endh())
        ret = *begin;

    return ret;
}
