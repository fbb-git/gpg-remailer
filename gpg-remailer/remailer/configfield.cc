#include "remailer.ih"

string Remailer::configField(string const &field)
{
    static Pattern pattern( R"(^\s*\S+\s+(\S+))" );  // pick 2nd term as [1]

    ConfigFile::const_iterator iter = 
                                d_argConfig.findRE(R"(^\s*)" + field + ':');
    if (iter == d_argConfig.end())
        return "";

    pattern << *iter;
    return pattern[1];
}
