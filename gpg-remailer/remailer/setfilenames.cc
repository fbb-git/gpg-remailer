#include "remailer.ih"

void Remailer::setFilenames()
{
    string prefix;

    if (not d_arg.option(&prefix, 't'))
        prefix = configField("tmp");

    if (prefix.empty())
        prefix = "tmp/";

    if (prefix.back() != '/')               // make sure / is appended
        prefix += '/';

    d_decryptedName = prefix + "decrypted.";
    d_errName = prefix + "err.";
    d_mailName = prefix + "mail.";
    d_multipartSignedDataName = prefix + "multipartsigned.";
    d_contentsName = prefix + "org.";
    d_hdrsName = prefix + "hdrs.";
    d_reencryptName = prefix + "reencrypt.";
    d_reencryptedName = prefix + "reencrypted.";
    d_signatureName = prefix + "signature.";

    setSuffixNr();
        
    d_decryptedName += d_nr;
    d_errName += d_nr;
    d_mailName += d_nr;
    d_multipartSignedDataName += d_nr;
    d_contentsName += d_nr;
    d_hdrsName += d_nr;
    d_reencryptName += d_nr;
    d_reencryptedName += d_nr;
    d_signatureName += d_nr;
}
