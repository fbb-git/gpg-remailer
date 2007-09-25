#include "main.ih"

int main(int argc, char **argv)
try
{
    if (argc > 1)
        usage(argv[0]);

    string line;

    while (getline(cin, line))
    {
        cout << line << endl;                           // copy a line

        if (line == "-----BEGIN PGP MESSAGE-----")      // found the marker
            filter();                                   // filter PGP section
    }
    return 0;
}
catch (int retVal)
{
    return retVal;
}
