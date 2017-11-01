#include "cleartextmail.ih"

string ClearTextMail::mailCommand(string const &recipient) const
{
std::cerr << __FILE__": headers: " << headers(false) << '\n';

    return
        "/usr/bin/mail -s '" + subject() + "' "
                "-a \"Reply-To: " + d_replyTo + "\" " +
                headers(false) + " " + recipient;
}
