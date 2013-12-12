#include "gpgmail.ih"

GPGMail::GPGMail(Log &log, Headers &headers, string const &mailName, 
                string const &replyTo, string const &step, bool relax)
:
    Mailer(log, headers, mailName, replyTo, step),
    d_mailName(mailName),
    d_relax(relax),
    d_boundary(makeBoundary())
{
}
