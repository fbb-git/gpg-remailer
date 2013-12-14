#include "mailer.ih"

void Mailer::sendMail(string const &command, string const &label, 
                      string const &recipient, bool dontSend) 
{
    d_log << level(LOGCOMMANDS) << command << '\n';

    if (dontSend)
    {
        d_log << level(LOGDEBUG) << 
                 "Sending mail suppressed by config/option\n";
        return;
    }

    Spawn mail(command, d_mailName, "", "");
    mail.fork();

    d_log << level(LOGDEFAULT) << 
             label << " (" << d_subject << ") sent to " << recipient << '\n';
}
