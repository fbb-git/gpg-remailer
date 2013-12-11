#include "cleartextmail.ih"

void ClearTextMail::writeMailContents(std::string const &destination)
{
    ifstream in;
    Exception::open(in, d_mailSource);

    ofstream out;
    Exception::open(out, destination);

    out << in.rdbuf();
    out.close();
}
