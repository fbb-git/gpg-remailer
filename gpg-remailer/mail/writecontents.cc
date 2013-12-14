#include "mail.ih"

Enums::MailType Mail::writeContents(std::string const &contentsName)
{
    d_log << level(LOGDEBUG) << "Original mail contents to " << 
                                contentsName << '\n';
    ofstream out;
    LogException::open(out, contentsName);

    if (not PGPmessage(out))
    {
        if (not d_clearTextAccepted)
            throw LogException() << "not PGP encrypted e-mail\n";

        d_log << level(LOGDEFAULT) << "Clear-text mail\n";
        return CLEAR;
    }
    filter(out);
    return ENCRYPTED;
}
