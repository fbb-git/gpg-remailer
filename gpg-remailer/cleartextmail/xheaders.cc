#include "cleartextmail.ih"

string ClearTextMail::xHeaders() const
{
    string ret;

    if (not Arg::instance().option('x'))
        return ret;

    ret = R"( -a X-from:")" + d_headers[0].substr(d_headers.find(' '));
    
    for (size_t idx = 1, end = d_headers.size(); idx != end; ++idx)
    {
        string const &hdr = d_headers[idx];
        if (hdr.find("envelope") != string::npos)
            ret += R"( -a X-envelope:")" + hdr.substr(hdr.find(' '));
        else if (hdr.find("From: ") != string::npos)
            ret += R"( -a X-From:")" + hdr.substr(hdr.find(' '));
    }

    return ret;
}
