#include "remailer.ih"

void Remailer::mail()
{
    if (!step("mail"))
        return;

    MailStruct mailStruct = {makeBoundary(), d_mailName, d_subject,
                             d_replyTo,
                             d_log,
                             d_arg.option(0, "no-mail") || 
                                    configField("noMail") == "true"};

    writeMail(mailStruct.boundary);

    for_each(d_recipients.begin(), d_recipients.end(), 
        FnWrap1c<string const &, MailStruct const &>
                (sendMail, mailStruct));
}
