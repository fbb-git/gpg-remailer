#include "remailer.ih"

void Remailer::setSigRequired()
{
    string signatureRequired = configField("signature");
    d_sigRequired = 
        signatureRequired == "good"     ? GOOD_SIGNATURE :
        signatureRequired == "required" ? SIGNATURE_FOUND :
                                          NO_SIGNATURE;
}
