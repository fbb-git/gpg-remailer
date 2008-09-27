#include "remailer.ih"

void Remailer::setFilenames()
{
    string prefix = configField("^\\s*tmp:");

    if (prefix == "")
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

    string id = idSuffix();
        
    d_orgName += id;
    d_decryptedName += id;
    d_signatureName += id;
    d_reencryptName += id;
    d_reencryptedName += id;
    d_errName += id;
    d_mailName += id;
}
