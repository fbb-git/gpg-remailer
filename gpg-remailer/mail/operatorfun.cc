#include "mail.ih"

void Mail::operator()(MailType type, 
                      string const &contents,
                      string const &mailName,
                      string const &replyTo,
                      string const &step,
                      vector<string> const &configuredRecipients,
                      bool dontSend)
{
    d_mailNamePtr = &mailName;
    d_replyToPtr  = &replyTo;
    d_dontSend = dontSend;

    d_subject = getHeader("Subject");
    if (d_subject.empty())
        d_subject =  "Mail from the reencrypting remailer";

    vector<string> oneRecipient;

    d_log << level(LOGDEBUG) << "Mail to send written to " << 
                                mailName << '\n';

    (this->*(type == CLEAR ? &Mail::clearTextMail : &Mail::pgpMail))(
        contents,
        setRecipients(step, oneRecipient, configuredRecipients)
    );

//    MailProcessor &mailProcessor = 
//        type == CLEAR ? ClearTextMail(d_log, d_headers, mailName,
//        &Mail::clearTextMail : &Mail::pgpMail))( 
}



