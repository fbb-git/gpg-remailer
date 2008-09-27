#include "remailer.ih"

void Remailer::copyTo(ostream &out, istream &in, string const &boundary)
{
    string line;
    while (getline(in, line))
    {
        out << line << endl;
        if (line.find(boundary) == 0)
            return;
    }
}
