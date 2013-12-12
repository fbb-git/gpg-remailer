#include "cleartextmail.ih"

ClearTextMail::ClearTextMail(Log &log, Headers &headers, 
                        string const &mailName,
                        string const &replyTo,
                        string const &step)
:
    Mailer(log, headers, mailName, step),
    d_headers(headers),
    d_mailName(mailName),
    d_replyTo(replyTo)
{
}
