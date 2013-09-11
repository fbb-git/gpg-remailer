#include "remailer.ih"

void Remailer::decrypt()
{
    if (!step("dec"))
        return;

    gpg("--decrypt " + d_gpgOptions, 
        d_orgName, d_decryptedName, d_signatureName);


//    command << "--decrypt " << d_gpgOptions << 
//            " < " << d_orgName << 
//            " >> " << d_decryptedName <<
//            " 2>> " << d_signatureName;
//
//    gpg(command.str());
}
