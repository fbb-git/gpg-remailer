#include "remailer.ih"

void Remailer::sendMail(string const &recipient, string const &subject,
                        string const &boundary)
{
    string command =  d_mailType == CLEAR?
                        clearMailCommand(recipient, subject)
                    :
                        pgpMailCommand(recipient, subject, boundary);

    d_log << level(LOGCOMMANDS) << command << '\n';

    if (d_arg.option(0, "no-mail") || configField("noMail") == "true")
    {
        d_log << level(LOGDEBUG) << 
                 "Sending mail suppressed by config/option\n";
        return;
    }

    Spawn mail(d_log, command, d_mailName, "", "");
    mail.fork();

    ms.log << level(LOGDEFAULT) << "Reencrypted mail (" << subject << 
                                   ") sent to " << recipient << '\n';
}




