#include "main.ih"

void filter()
{
    string line;

    while (getline(cin, line))
    {
        if (line != "-----END PGP MESSAGE-----")
            inspect(line);
        else
        {
            cout << line << endl;
            return;
        }
    }
}
        

