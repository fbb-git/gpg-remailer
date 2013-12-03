#include "remailer.ih"

    // static member, hence ms needs the log field.
void Remailer::sendMail(string const &recipient, MailStruct const &ms)
{
    ostringstream command;

    command << "/usr/bin/mail -s '" << ms.subject << "' "
                "-a \"Reply-To: " << ms.replyTo << "\" "
                "-a 'Content-Type: multipart/encrypted; "
                R"(protocol="application/pgp-encrypted"; )"
                R"(boundary=")" << ms.boundary << R"("' )" <<
                recipient;

    ms.log << level(LOGCOMMANDS) << command.str() << '\n';

    if (ms.nomail)
    {
        ms.log << level(LOGDEBUG) << 
                    "Sending mail suppressed by config/option\n";
        return;
    }

    Spawn mail(ms.log, command.str(), ms.mailName, "", "");
    mail.fork();

    ms.log << level(LOGDEFAULT) << "Reencrypted mail (" << ms.subject << 
                                   ") sent to " << recipient << '\n';
}




