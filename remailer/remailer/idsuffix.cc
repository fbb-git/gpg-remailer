#include "remailer.ih"

string Remailer::idSuffix()
{
    string id;

    bool random = !d_arg.option(&id, 'n');

    if (!random)
        d_keepFiles = true;
    else
    {
        IRandStream rs(1, 99999, time(0));
        string name(d_orgName);
        size_t value;

        do
        {
            rs >> value;
            string name = d_orgName + static_cast<string>(X2a(value));
        } 
        while (Stat(name));
        id = X2a(value);
    }

    msg() << "File IDs will be: " << id << " (" <<
                                    (random ? "random" : "via --nr") <<
                                    ")" << info;

    return id;
}
