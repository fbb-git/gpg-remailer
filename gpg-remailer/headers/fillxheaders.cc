#include "headers.ih"

void Headers::fillXheaders()
{
    auto iter = begin();

                            // always use the official envelope
    d_xHeaders = R"( -a "X-GPG-remailer-from: )" + 
                        String::escape(iter->substr(iter->find(' '))) + '"';
    
    for (++iter; iter != end(); ++iter)     // visit all remaining headers
    {
        string const &hdr = *iter;

        if (hdr.find("envelope") != string::npos)
            d_xHeaders += R"( -a "X-GPG-remailer-envelope: )" + 
                        String::escape(hdr.substr(hdr.find(' '))) + '"';

        else if (hdr.find("From: ") != string::npos)
            d_xHeaders += R"( -a "X-GPG-remailer-From: )" + 
                        String::escape(hdr.substr(hdr.find(' '))) + '"';
    }
}
