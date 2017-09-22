#include "remailer.ih"

void Remailer::mail()
{
    if (step("pgpmail"))
        d_mailType = ENCRYPTED;
    else if (step("clearmail"))
        d_mailType = CLEAR;
    else if (d_mailType == UNKNOWN)
        return;

    d_mail(d_mailType, 
           d_mailType == CLEAR ? d_contentsName : d_reencryptedName, 
                not envelopeOK()            // specify 'dontSend'
                ||
                d_preamble.arg.option(0, "no-mail") 
                || 
                configField("noMail") == "true"
    );
}



