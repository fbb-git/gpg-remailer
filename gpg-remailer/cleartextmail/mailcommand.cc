#include "cleartextmail.ih"

string ClearTextMail::mailCommand(string const &recipient) const
{
    return
        "/usr/bin/mail -s '" + subject() + "' "
                "-a \"Reply-To: " + d_replyTo + "\" " +
                headers(processHeaders) + " " + recipient;
}
