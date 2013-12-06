#include "mail.ih"


bool Mail::PGPmessage(ostream &out)
{
    string line;
    while (getline(cin, line))
    {
        out << line << endl;                // copy a line

        if (line == "-----BEGIN PGP MESSAGE-----")      // found the marker
            return true;
    }
    return false;
}





