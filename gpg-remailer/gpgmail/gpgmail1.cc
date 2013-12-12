#include "gpgmail.ih"

GPGMail::GPGMail(Log &log, Headers &headers, string const &mailName, 
                string const &replyTo, string const &step, bool relax)
:
    Mailer(log, headers, mailName, step),
    d_mailName(mailName),
    d_replyTo(replyTo),
    d_relax(relax),
    d_boundary(makeBoundary())
{
}
