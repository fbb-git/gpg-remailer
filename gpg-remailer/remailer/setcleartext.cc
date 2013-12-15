#include "remailer.ih"

void Remailer::setClearText()
{
    string clearText = configField("clear-text");
    if (clearText.empty())
        clearText = "rejected (by default)";

    d_mail.setClearTextMode(
                     clearText == "accepted" || clearText == "envelope" ?
                        ACCEPTED
                    :
                        REJECTED
    );

    if (clearText != "envelope")
    {
        if (d_envelope.size())
        {
            d_log << level(LOGDEFAULT) << 
                "Envelope ignored (clear-text: " << clearText << ")\n";
            d_envelope.clear();
        }            
    }
    else
    {
        checkMembers(d_envelope);

        if (d_log.level() == LOGDEBUG)
        {
            d_log << "Accepted envelope addresses for clear-text e-mail:\n";
            for (auto &address: d_envelope)
                d_log << ' ' << address;
            d_log << '\n';
        }
    }
}
