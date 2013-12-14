#include "gpgmail.ih"

GPGMail::GPGMail(Log &log, Headers &headers, string const &mailName, 
                string const &replyTo, string const &step)
:
    Mailer(log, headers, mailName, step),
    d_mailName(mailName),
    d_replyTo(replyTo),
    d_boundary(makeBoundary())
{
}
