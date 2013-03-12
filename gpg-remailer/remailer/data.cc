#include "remailer.ih"

void (Remailer::*Remailer::s_reEncrypt[])(IOContext &) = 
{
    &Remailer::simple,
    &Remailer::multipart,
    &Remailer::multipartSigned
};
