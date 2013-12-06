#include "remailer.ih"

string Remailer::clearMailCommand(string const &recipient, string boundary)
{
    ostringstream command;


    if (d_mailType == ms.clearMail)
        command << "/usr/bin/mail -s '" << ms.subject << "' "
                "-a \"Reply-To: " << ms.replyTo << "\" " <<
                recipient;

    return command.str();
}




