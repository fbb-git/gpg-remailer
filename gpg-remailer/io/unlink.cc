#include "io.ih"

void IO::unlink(std::string const &name)
{
    if (::unlink(name.c_str()) != 0 && errno != ENOENT)
        throw LogException() << "Can't rm " << name;
}
