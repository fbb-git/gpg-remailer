#include "remailer.ih"

void (Remailer::*Remailer::s_reEncrypt[])(IOContext &) = 
{
    &Remailer::simple,
    &Remailer::multipart,
    &Remailer::multipartSigned
};

Remailer::StepStruct Remailer::s_step[] = 
    {
        {"hdrs",        UNKNOWN},
        {"org",         UNKNOWN},

        {"clearmail",   CLEAR},

        {"dec",         ENCRYPTED},
        {"doc",         ENCRYPTED},
        {"enc",         ENCRYPTED},
        {"pgpmail",     ENCRYPTED},
    };

Remailer::StepStruct *Remailer::s_stepEnd = 
                            s_step + sizeof(s_step) / sizeof(StepStruct);
