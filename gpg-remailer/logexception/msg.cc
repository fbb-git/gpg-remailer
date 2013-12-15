#include "logexception.ih"

char const *LogException::msg() const
{
    char const *cp = static_cast<exception const &>(*this).what();
    if (d_stdErr)
        cerr << cp;
    return cp;
}
