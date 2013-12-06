#include "mail.ih"

void Mail::writeContents(std::string const &contentsName)
{
    d_log << level(LOGDEBUG) << "Original mail contents in " << 
                                contentsName << '\n';

    ofstream out;

    IO::unlink(d_contentsName);

    if (not PGPmessage( IO::open(out, d_contentsName, d_relax) ))
    {
        if (d_clearText == ACCEPTED)
        {
            d_log << level(LOGDEFAULT) << "Clear-text mail\n";
            d_mailType = CLEAR;
            return;
        }
        d_log << level(LOGDEFAULT) << "Not PGP encrypted e-mail\n" << FATAL;
    }
    d_mailType = ENCRYPTED;
    filter(out);
}
