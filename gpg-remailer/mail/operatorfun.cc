#include "mail.ih"

void Mail::operator()(MailType type, 
                      string const &mailData,
                      bool dontSend)
{
//    if (type == ENCRYPTED)
//    {
//        PGPMail pgpMail(....);
//        send(pgpMail);
//    }
//    else
//    {
        ClearTextMail clearTextMail(d_log, d_headers, d_mailName, d_replyTo,
                                    d_step);
        clearTextMail.send(mailData, d_recipients, dontSend);
//    }
}



