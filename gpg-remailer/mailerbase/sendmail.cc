#include "mailerbase.ih"

void MailerBase::sendMail(string const &command, 
                          string const &label, 
                          string const &recipient, bool dontSend) 
{
    d_log << level(LOGCOMMANDS) << command << '\n';

    if (dontSend)
    {
        d_log << level(LOGDEBUG) << 
                 "Sending mail suppressed by config/option\n";
        return;
    }

    ifstream in(d_mailName);
    Process mail(FBB::Process::CIN | FBB::Process::IGNORE_COUT_CERR, command);

    mail.start();
    mail << in.rdbuf() << eoi;

    d_log << level(LOGDEFAULT) << 
             label << " (" << d_subject << ") sent to " << recipient << '\n';
}



