#include "remailer.ih"

void Remailer::filter(ostream &out)
{
    string line;

    while (getline(cin, line))
    {
        if (line != "-----END PGP MESSAGE-----")
            inspect(out, line);
        else
        {
            out << line << endl;
            return;
        }
    }
}
        

