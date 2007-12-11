#include "main.ih"

void inspect(std::string const &line)
{
    istringstream in(line);
    char c;

    while (in.get(c))
    {
        if (c != '=')
            cout.put(c);
        else
            hexChar(in);
    }

    cout << endl;
}
        

