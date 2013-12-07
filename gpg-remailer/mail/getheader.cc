#include "mail.ih"

string Mail::getHeader(char const *hdr)
{
    string ret;
        
    MailHeaders::const_hdr_iterator begin = mailHeader(hdr);
    if (begin != d_headers.endh())
        ret = *begin;

    return ret;
}
