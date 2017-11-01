#include "mailerbase.ih"

// static
void MailerBase::clearTextHeaders(string &contentHdr, string const &hdr)
{
    if (contentHeader(hdr.c_str()))
        contentHdr += cleanupHeader(hdr);
                                                // add the encountered header
                                                // to the reencrypted mail
}
