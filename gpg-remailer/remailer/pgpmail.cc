#include "remailer.ih"

bool Remailer::pgpMail()
{
    if (!step("org"))
        return true;

    d_log << level(LOGDEBUG) << "Original file in " << d_orgName << '\n';

    ofstream out;

    if (not PGPmessage( open(out, d_orgName, UNLINK) ))
    {
        if (d_clearText == ACCEPTED)
        {
            d_log << level(LOGDEFAULT) << "Clear-text mail\n";
            d_mailType = CLEAR;
            return false;
        }
        d_log << level(LOGDEFAULT) << "Not PGP encrypted e-mail\n" << FATAL;
    }
    filter(out);
    return true;
}
