#include "remailer.ih"

void Remailer::preparations()
{
    checkRelax();
    setKeepFiles();
    setDebug();

    d_log << level(LOGDEBUG) << 
        "User: " << d_preamble.user.name() << " (" << 
                    d_preamble.user.userid() << ")\n";

    setFilenames();                         // define all used filenames 

    multiField(d_members, "member", 'm', true);
    multiField(d_recipients, "recipient", 'r', true);
    multiField(d_envelope, "envelope", 'e', false);

    checkMembers(d_recipients);

    setReplyTo();
    setSigRequired();
    setUmask();

    if (step("hdrs"))
        d_mail.writeHeaders(d_hdrsName);

    setClearText();
}







