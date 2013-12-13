#include "remailer.ih"

bool Remailer::envelopeOK()
{
    if (d_mailType == CLEAR && d_envelope.size())
    {
        istringstream envelope(d_headers[0]);
        string address;
        envelope >> address >> address;     // skips 'From '

        for (auto &envelope: d_envelope)
        {
            if (String::casecmp(envelope, address) == 0)
                return true;
        }
        
        d_log << level(LOGDEFAULT) << "Envelope address " << address <<
                    " not accepted for clear-text e-mail\n";
        return false;
    }
    return true;
}
