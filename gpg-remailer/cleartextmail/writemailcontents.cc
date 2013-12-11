#include "cleartextmail.ih"

void ClearTextMail::writeMailContents(std::string const &mailData) const
{
    ifstream in;
    Exception::open(in, mailData);

    ofstream out;
    Exception::open(out, d_mailName);

    out << in.rdbuf();
}
