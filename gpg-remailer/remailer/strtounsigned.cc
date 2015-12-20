#include "remailer.ih"

unsigned long Remailer::strToUnsigned(string const &str, 
                                      char const *optionName, size_t base) 
try
{
    return stoul(str, 0, base);
}
catch (...)
{
    throw Exception() << "expected a number setting " << optionName << 
                         ", received: `" << str << '\'';
}

