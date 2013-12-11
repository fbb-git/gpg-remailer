#include "cleartextmail.ih"

ClearTextMail::ClearTextMail(Log &log, Headers &headers, 
                        string const &mailName,
                        string const &replyTo,
                        string const &step)
:
    Mailer(log, headers, mailName, replyTo, step),
    d_headers(headers),
    d_mailName(mailName)
{
}
