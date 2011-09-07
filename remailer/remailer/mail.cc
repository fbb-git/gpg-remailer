#include "remailer.ih"

void Remailer::mail()
{
    if (!step("mail"))
        return;

    string subject = d_subject.empty() ? 
                        "Mail from the reencrypting remailer"
                     : 
                         d_subject;

    MailStruct mailStruct = {makeBoundary(), d_mailName, 
                             subject,
                             d_replyTo,
                             d_log,
                             d_arg.option(0, "no-mail") || 
                                    configField("noMail") == "true"};

    writeMail(mailStruct.boundary);

    size_t pos = d_step.find(':');

    if (pos != string::npos)
    {
        string recipient = d_step.substr(pos + 1); 

        d_log << level(LOGDEFAULT) << "Ignoring recipients, mail sent to " <<
                 recipient << '\n';
        sendMail(recipient, mailStruct);
    }
    else
    {
        for_each(d_recipients.begin(), d_recipients.end(),
            [&](string const &line)
            {
                sendMail(line, mailStruct);
            }
        );
    }
}



