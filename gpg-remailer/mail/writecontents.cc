#include "mail.ih"

Enums::MailType Mail::writeContents(std::string const &contentsName)
{
    d_log << level(LOGDEBUG) << "Original mail contents to " << 
                                contentsName << '\n';
    ofstream out;

    IO::unlink(contentsName);

    if (not PGPmessage( IO::open(out, contentsName, d_relax) ))
    {
        if (d_clearTextAccepted)
        {
            d_log << level(LOGDEFAULT) << "Clear-text mail\n";
            return CLEAR;
        }
        d_log << level(LOGDEFAULT) << "Not PGP encrypted e-mail\n" << FATAL;
    }
    filter(out);
    return ENCRYPTED;
}
