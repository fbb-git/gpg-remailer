#include "mail.ih"

void Mail::writeHeaders(std::string const &hdrsName)
{
    ofstream out;                       // write the mail headers to file
    Exception::open(out, d_hdrsName);

    for (auto &hdr: d_mailHeaders)
        out << hdr << '\n';
}
