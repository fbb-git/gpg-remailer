#include "mail.ih"

void Mail::writeHeaders(std::string const &hdrsName)
{
    ofstream out;                       // write the mail headers to file
    Exception::open(out, hdrsName);

    for (auto &hdr: d_headers)
        out << hdr << '\n';

    d_log << level(LOGDEBUG) << "Headers written to " << hdrsName << '\n';
}
