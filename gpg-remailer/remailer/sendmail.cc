#include "remailer.ih"

void Remailer::sendMail(string const &recipient, MailStruct const &ms)
{
    ostringstream command;

    command << "/usr/bin/mail -s '" << ms.subject << "' "
                "-a \"Reply-To: " << ms.replyTo << "\" "
                "-a 'Content-Type: multipart/encrypted; "
                    "protocol=\"application/pgp-encrypted\"; "
                    "boundary=\"" << ms.boundary << "\"' " <<
                recipient << " < " << ms.mailName;

    ms.log << level(LOGCOMMANDS) << command.str() << '\n';

    if (ms.nomail)
    {
        ms.log << level(LOGDEBUG) << 
                    "Sending mail suppressed by config/option\n";
        return;
    }

    Process mailProc(0, command.str());
    mailProc.system();
    mailProc.waitForChild();

    ms.log << level(LOGDEFAULT) << "Reencrypted mail (" << ms.subject << 
                                   ") sent to " << recipient << '\n';
}





