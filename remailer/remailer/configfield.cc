#include "remailer.ih"

string Remailer::configField(string const &field)
{
    static Pattern pattern("^\\s*\\S+\\s+(\\S+)");  // pick 2nd term as [1]

    ConfigFile::const_iterator iter = d_config.findRE(field);

    if (iter == d_config.end())
        return "";

    pattern << *iter;
    return pattern[1];
}
