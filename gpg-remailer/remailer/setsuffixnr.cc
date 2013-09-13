#include "remailer.ih"

void Remailer::setSuffixNr()
{
    bool random = d_nr.empty();

    if (random)
    {
        IRandStream rs(1, 99999, time(0));
        string name(d_orgName);
        size_t value;

        do
        {
            rs >> value;
            string name = d_orgName + to_string(value);
        } 
        while (Stat(name));
        d_nr = to_string(value);
    }

    d_log << level(LOGDEBUG) << "File Nrs will be: " << d_nr << " (" <<
                                    (random ? "random" : "via --nr") << ")\n";
}
