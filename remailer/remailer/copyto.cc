#include "remailer.ih"

void Remailer::copyTo(ostream &out, istream &in)
{
    string line;
    while (getline(in, line))
    {
        out << line << endl;
        if (line.find(d_boundary) == 0)
            return;
    }
}
