#include "main.ih"

void inspect(std::string const &line)
{
    istringstream in(line);
    char c;

    while (in.get(c))
        cout.put(c == '=' ? hexChar(in) : c);

    cout << endl;
}
        

