#include "remailer.ih"

// the boundary has just been seen

void Remailer::copyToBoundary(string const &destName, istream &in)
{
    ofstream out;
    
    copyToBoundary( IO::open(out, destName, d_relax), in);
}
