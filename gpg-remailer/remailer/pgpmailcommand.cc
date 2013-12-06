#include "remailer.ih"

string Remailer::pgpMailCommand(string const &recipient, string boundary)
{
    ostringstream command;

    command << "/usr/bin/mail -s '" << ms.subject << "' "
                "-a \"Reply-To: " << ms.replyTo << "\" "
                "-a 'Content-Type: multipart/encrypted; "
                R"(protocol="application/pgp-encrypted"; )"
                R"(boundary=")" << ms.boundary << R"("' )" <<
                recipient;

    return command.str();
}

