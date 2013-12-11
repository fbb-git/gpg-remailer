//#include "mail.ih"
//
//void Mail::send(string const &contents, Mailer &mailer, bool dontSend)
//{
//    d_subject = getHeader("Subject");
//    if (d_subject.empty())
//        d_subject =  "Mail from the reencrypting remailer";
//
//    vector<string> oneRecipient;
//
//    d_log << level(LOGDEBUG) << "Mail to send written to " << 
//                                d_mailName << '\n';
//    mailer.send(
//        contents, 
//        setRecipients(oneRecipient, d_recipients),
//        subject
//    );
//}
