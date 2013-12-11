//#include "mail.ih"
//
//void Mail::sendMail(string const &command, string const &label, 
//                    string const &recipient) 
//{
//    d_log << level(LOGCOMMANDS) << command << '\n';
//
//    if (d_dontSend)
//    {
//        d_log << level(LOGDEBUG) << 
//                 "Sending mail suppressed by config/option\n";
//        return;
//    }
//
//    Spawn mail(d_log, command, *d_mailNamePtr, "", "");
//    mail.fork();
//
//    d_log << level(LOGDEFAULT) << 
//             label << " (" << d_subject << ") sent to " << recipient << '\n';
//}
