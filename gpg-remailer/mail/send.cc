#include "mail.ih"

void Mail::send(string const &contents, Mailer &mailer)
{
    string subject = getHeader("Subject");
    if (subject.empty())
        subject =  "Mail from the reencrypting remailer";

    vector<string> oneRecipient;

    d_log << level(LOGDEBUG) << "Mail to send written to " << 
                                d_mailName << '\n';
    mailer.send(
        contents, 
        setRecipients(oneRecipient, d_recipients),
        subject
    );
}
