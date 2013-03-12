#include "remailer.ih"

bool Remailer::PGPmessage(ostream &out)
{
    static Pattern subject("^Subject:\\s*");

    string line;
    
    while (getline(cin, line))
    {
        out << line << endl;                      // copy a line

        if (subject << line)
        {
            d_subject = subject.beyond();

            rmQuotes(d_subject);
            d_log << level(LOGDEBUG) << "Subject: " << d_subject << '\n';
        }
            
        if (line == "-----BEGIN PGP MESSAGE-----")      // found the marker
            return true;
    }
    return false;
}
