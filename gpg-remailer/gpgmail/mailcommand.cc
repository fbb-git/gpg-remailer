#include "gpgmail.ih"

string GPGMail::mailCommand(string const &recipient) const
{
    return
        "/usr/bin/mail -s '" + subject() + "' "
                "-a \"Reply-To: " + d_replyTo + "\" " +
                headers(&processHeaders) + 
                " -a 'Content-Type: multipart/encrypted; "
                    R"(protocol="application/pgp-encrypted"; )"
                    R"(boundary=")" + d_boundary + R"("' )" +
                recipient;
}

