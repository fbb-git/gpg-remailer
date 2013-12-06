#include "remailer.ih"

MailHeaders::const_hdr_iterator Remailer::mailHeader(std::string const &hdr)
{
    d_mailHeaders.setHeaderIterator("Subject");
    return d_mailHeaders.beginh();
}
