#include "remailer.ih"

void Remailer::decrypt()
{
    if (!step("dec"))
        return;
                            // decrypt the original file, write new files
                            // containing the decrypted info and the signature
    gpg("--decrypt ",                   
        d_orgName, d_decryptedName, d_signatureName);
}
