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

    msg() << "\n" << command.str() << info;

    Process mailProc(command.str());
    mailProc.system();
    mailProc.wait();
}
