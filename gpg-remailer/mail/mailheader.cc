#include "mail.ih"

MailHeaders::const_hdr_iterator Mail::mailHeader(char const *hdr)
{
    d_headers.setHeaderIterator(hdr, MailHeaders::CASE_FULL);
    return d_headers.beginh();
}
