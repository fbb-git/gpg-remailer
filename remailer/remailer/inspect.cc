#include "remailer.ih"

void Remailer::inspect(ostream &out, string const &line)
{
    istringstream in(line);
    char c;

    while (in.get(c))
    {
        if (c != '=')
            out.put(c);
        else
            hexChar(out, in);
    }

    out << endl;
}
        

