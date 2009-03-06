#include "remailer.ih"

Remailer::~Remailer()
{
    if (d_keepFiles)
        return;

    unlink(d_decryptedName.c_str());
    unlink(d_errName.c_str());
    unlink(d_mailName.c_str());
    unlink(d_multipartSignedDataName.c_str());
    unlink(d_orgName.c_str());
    unlink(d_reencryptName.c_str());
    unlink(d_reencryptedName.c_str());
    unlink(d_signatureName.c_str());
}
