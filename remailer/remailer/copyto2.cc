#include "remailer.ih"

// the boundary has just been seen

void Remailer::copyTo(string const &destName, istream &in)
{
    ofstream out;
    ofopen(destName, &out);

    string line[2];
    string *last = &line[0];
    string *next = &line[1];

    getline(in, *last);
    while (getline(in, *next) && !foundIn(*next, d_boundary))
    {
        out << *last << endl;
        swap(last, next);
    }
}