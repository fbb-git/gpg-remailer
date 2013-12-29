#include "mailerbase.ih"

MailerBase::MailerBase(FBB::Log &log, Headers &headers, 
               std::string const &mailName, std::string const &step)
:
    d_log(log),
    d_headers(headers),
    d_mailName(mailName),
    d_step(step),
    d_subject(d_headers.getHeader("Subject"))
{
    if (d_subject.empty())
        d_subject =  "Mail from the reencrypting remailer";

    d_log << FBB::level(LOGDEBUG) << "Mail to send written to " << 
                                                        mailName << '\n';
}

