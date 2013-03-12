#include "remailer.ih"

void Remailer::testPermissions(string const &path, size_t permissions)
{
    if (d_relax)
        return;

    Stat stat(path);

    if (stat.mode() & ~permissions)
    {
        ostringstream out;
        out  << path << 
                " permission required: 0" << oct << permissions <<
                ", actual: 0" << stat.mode() << '\n';
        cerr << out.str();
        d_log << out.str() << '\n' << FATAL;
    }
}
