#include "mailer.ih"

Mailer::Mailer(Log &log, Headers &headers, 
                string const &mailName, string const &replyTo,
                string const &step)
:
    d_log(log),
    d_headers(headers),
    d_mailName(mailName),
    d_replyTo(replyTo),
    d_step(step),
    d_subject(d_headers.getHeader("Subject"))
{
    if (d_subject.empty())
        d_subject =  "Mail from the reencrypting remailer";

    d_log << level(LOGDEBUG) << "Mail to send written to " << 
                                                        mailName << '\n';
}
