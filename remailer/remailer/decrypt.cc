#include "remailer.ih"

void Remailer::decrypt()
{
    if (!step("dec"))
        return;

    ostringstream command;

    command << "--decrypt " << d_gpgOptions << 
            " < " << d_orgName << 
            " > " << d_decryptedName <<
            " 2> " << d_signatureName;

    gpg(command.str());
}
