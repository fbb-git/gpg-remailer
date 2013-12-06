#include "remailer.ih"

void Remailer::decrypt()
{
    if (not step("dec") || d_mailType == ENCRYPTED))
        return;
                            // decrypt the original file, write new files
                            // containing the decrypted info and the signature

    d_gpg.decrypt(d_orgName, d_decryptedName, d_signatureName);
}
