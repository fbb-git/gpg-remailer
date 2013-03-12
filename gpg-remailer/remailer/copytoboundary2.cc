#include "remailer.ih"

// the boundary has just been seen

void Remailer::copyToBoundary(string const &destName, istream &in)
{
    ofstream out;
    ofopen(destName, &out);

    copyToBoundary(out, in);
}
