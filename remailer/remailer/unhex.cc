#include "remailer.ih"

void Remailer::unhex()
{
    if (!step("org"))
        return;

    d_log << level(LOGDEBUG) << "Original PGP file in " << d_orgName << '\n';

    ofstream out;
    Msg::open(out, d_orgName);

    if (!PGPmessage(out))
    {
        d_log << level(LOGDEFAULT) << "Not a PGP encrypted e-mail\n";
        throw Errno();
    }

    filter(out);
}
