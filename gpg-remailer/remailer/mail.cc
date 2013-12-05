#include "remailer.ih"

void Remailer::mail()
{
    if (!step("mail") && !step("clr"))
        return;

    string subject = d_subject.empty() ? 
                        "Mail from the reencrypting remailer"
                     : 
                         d_subject;

    if (step("clr"))
        d_mailType = CLEAR;

    MailStruct mailStruct = {makeBoundary(), d_mailName, 
                             subject,
                             d_replyTo,
                             d_log,
                             d_arg.option(0, "no-mail") || 
                                    configField("noMail") == "true",
                             d_mailType == CLEAR
                            };

    writeMail(mailStruct.boundary); // construct the mail from reencrypted.x
                                    // or (with CLEAR mail) org.x

    size_t pos = d_step.find(':');  // any explicit mail recipient?

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



