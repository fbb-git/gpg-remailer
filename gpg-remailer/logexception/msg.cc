#include "logexception.ih"

char const *LogException::msg() const
{
    char const *cp = exception::what();
    if (d_stdErr)
        cerr << cp << '\n';
    return cp;
}
