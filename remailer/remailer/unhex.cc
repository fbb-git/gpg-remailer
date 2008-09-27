#include "remailer.ih"

void Remailer::unhex()
{
    if (!step("org"))
        return;

    msg() << "Original PGP file in " << d_orgName << info;

    ofstream out;
    Msg::open(out, d_orgName);

    if (!PGPmessage(out))
        throw Errno(1, "Not a PGP encrypted e-mail");

    filter(out);
}
