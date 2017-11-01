#include "gpgmail.ih"

// static
void GPGMail::processHeaders(string &contentHdr, string const &hdr)
{
    if (contentHeader(hdr.c_str()))
        return;
                                                // add the encountered header
                                                // to the reencrypted mail
    contentHdr += cleanupHeader(hdr);
}
