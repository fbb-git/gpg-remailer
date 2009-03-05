#include "remailer.ih"

void (Remailer::*Remailer::s_reEncrypt[])(ostream &, istream &) = 
{
    &Remailer::simple,
    &Remailer::multipart,
    &Remailer::multipartSigned
}
