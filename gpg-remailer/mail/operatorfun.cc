#include "mail.ih"

void Mail::operator()(MailType type, 
                      string const &mailData,
                      bool dontSend)
{
    d_log << level(LOGDEBUG) << "Mail to send is written to " << 
                                d_mailName << '\n';
    if (type == ENCRYPTED)
        mail(mailData, dontSend, 
            GPGMail{ d_log, d_headers, d_mailName, d_replyTo, d_step} );
    else
        mail(mailData, dontSend, 
            ClearTextMail{ d_log, d_headers, d_mailName, d_replyTo, d_step });
}



