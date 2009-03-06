#include "remailer.ih"

void Remailer::copyToBoundary(ostream &out, istream &in)
{
    string line[2];
    string *last = &line[0];
    string *next = &line[1];

    getline(in, *last);
    while (getline(in, *next))
    {
        if (foundIn(*next, d_boundary))
            return;

        out << *last << endl;
        swap(last, next);
    }

    msg() << "No " << d_boundary << " boundary separator found in "
                "multipart MIME file" << fatal;
}
