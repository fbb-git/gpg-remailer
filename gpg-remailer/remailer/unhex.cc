#include "remailer.ih"

void Remailer::unhex()
{
    if (!step("org"))
        return;

    d_log << level(LOGDEBUG) << "Original PGP file in " << d_orgName << '\n';

    ofstream out;

    if (!PGPmessage(open(out, d_orgName, UNLINK)))
        d_log << level(LOGDEFAULT) << "Not a PGP encrypted e-mail\n" << FATAL;

    filter(out);
}
