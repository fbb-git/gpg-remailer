#include "mail.ih"

Mail::Mail(Log &log, string const &mailName,
           string const &replyTo, string const &step,
           vector<string> const &recipients,
           bool relax)
:
    d_log(log),
    d_mailName(mailName),
    d_replyTo(replyTo),
    d_step(step),
    d_recipients(recipients),
    d_relax(relax)
{}
