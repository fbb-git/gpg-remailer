#include "remailer.ih"

void Remailer::ofopen(string const &name, ofstream *out)
{
    ofstream tmp;

    if (!out)
        out = &tmp;

    out->open(name.c_str());

    if (!*out || chmod(name.c_str(), S_IRUSR | S_IWUSR ) != 0)
        d_log << "Can't create " << name << '\n' << FATAL;
}
