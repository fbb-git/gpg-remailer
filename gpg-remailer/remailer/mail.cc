#include "remailer.ih"

void Remailer::mail()
{
    if (step("pgpmail"))
        d_mailType = ENCRYPTED;
    else if (step("clearmail"))
        d_mailType == CLEAR;
    else if (d_mailType == UNKNOWN)
        return;

    d_mail(d_mailType, d_mailName, d_replyTo, d_step, d_recipients);



    MailHeaders::const_hdr_iterator begin = mailHeader("Subject", FULL);
    string subject = begin == d_mailHeaders.endh() ? 
                        "Mail from the reencrypting remailer"
                     : 
                         *begin;

//    MailStruct mailStruct = {makeBoundary(), d_mailName, 
//                             subject,
//                             d_replyTo,
//                             d_log,
//                             d_arg.option(0, "no-mail") || 
//                                    configField("noMail") == "true",
//
//                            };


    string boundary = makePGPBoundary();

    writeMail(boundary);            // construct the mail text 
                                    // from reencrypted.x
                                    // or (with CLEAR mail) org.x

    size_t pos = d_step.find(':');  // any explicit mail recipient?

    if (pos != string::npos)        // yes: send the mail to that recipient
    {
        string recipient = d_step.substr(pos + 1); 

        d_log << level(LOGDEFAULT) << "Ignoring recipients, mail sent to " <<
                 recipient << '\n';
        sendMail(recipient, subject, boundary);
    }
    else                        // no, send the mail to each recipient
    {
        for(auto const &recipient: d_recipients)
            sendMail(recipient, subject, boundary);
    }
}



