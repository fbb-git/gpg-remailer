#include "cleartextmail.ih"

string ClearTextMail::mailCommand(string const &recipient) const
{
std::cerr << __FILE__": headers: " << headers(&processHeaders) << '\n';

    return
        "/usr/bin/mail -s '" + subject() + "' "
                "-a \"Reply-To: " + d_replyTo + "\" " +
                headers(processHeaders) + " " + recipient;
}
