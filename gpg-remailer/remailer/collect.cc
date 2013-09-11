#include "remailer.ih"

void Remailer::collect(ostream *out, istream *in)
{
    *out << in->rdbuf();
}
