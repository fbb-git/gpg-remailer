#include "remailer.ih"

void Remailer::decrypt()
{
    if (!step("dec"))
        return;

    gpg("--decrypt ",
        d_orgName, d_decryptedName, d_signatureName);
}
