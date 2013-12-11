#include "mail.ih"

void Mail::operator()(MailType type, 
                      string const &contents,
//                      string const &mailName,
//                      string const &replyTo,
//                      string const &step,
//                      vector<string> const &configuredRecipients,
                      bool dontSend)
{
    if (type == CLEAR)
    {
        PGPMail pgpMail(....);
        send(pgpMail);
    }
//    else
//    {
//        ClearTextMail clearTextMail(d_headers, d_mailName);
//        send(clearTextMail)
//    }

//
//    
//
//    (this->*(type == CLEAR ? &Mail::clearTextMail : &Mail::pgpMail))(
//        contents,
//        setRecipients(step, oneRecipient, configuredRecipients)
//    );
}



