#include "remailer.ih"

void Remailer::setFilenames()
{
    string prefix = configField("tmp");

    if (prefix.empty())
        prefix = "tmp/";

    if (*prefix.rbegin() != '/')          // make sure / is appended
        prefix += '/';

    d_orgName = prefix + "org.";
    d_decryptedName = prefix + "decrypted.";
    d_signatureName = prefix + "signature.";
    d_reencryptName = prefix + "reencrypt.";
    d_reencryptedName = prefix + "reencrypted.";
    d_errName = prefix + "err.";
    d_mailName = prefix + "mail.";

    setSuffixNr();
        
    d_orgName += d_nr;
    d_decryptedName += d_nr;
    d_signatureName += d_nr;
    d_reencryptName += d_nr;
    d_reencryptedName += d_nr;
    d_errName += d_nr;
    d_mailName += d_nr;
}
