#include "mail.ih"

void Mail::operator()(MailType type, 
                      string const &mailData,
                      bool dontSend)
{
    d_log << level(LOGDEBUG) << "Mail to send is written to " << 
                                d_mailName << '\n';

    if (type == ENCRYPTED)
    {
        GPGMail gpgMail(d_log, d_headers, d_mailName, d_replyTo, d_step);
        gpgMail.send(mailData, d_recipients, dontSend);
    }
    else
    {
        ClearTextMail clearTextMail(d_log, d_headers, d_mailName, d_replyTo,
                                    d_step);
        clearTextMail.send(mailData, d_recipients, dontSend);
    }
}



