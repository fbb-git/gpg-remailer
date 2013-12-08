#include "remailer.ih"

void Remailer::decrypt()
{
    if (d_mailType == ENCRYPTED || step("dec"))
        d_gpg.decrypt(d_contentsName, d_decryptedName, d_signatureName);
                            // decrypt the original file, write new files
                            // containing the decrypted info and the signature
}
