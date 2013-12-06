#include "remailer.ih"

void Remailer::testPermissions(string const &path, size_t permissions)
{
    if (d_relax)
        return;

    Stat stat(path);

    if (stat.mode() & ~permissions)
        throw LogException(true) << path << 
                " permission required: 0" << oct << permissions <<
                ", actual: 0" << stat.mode();
}
