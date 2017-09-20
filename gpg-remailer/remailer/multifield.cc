#include "remailer.ih"

void Remailer::multiField(vector<string> &dest, char const *keyWord, int opt,
                          bool needElements)
{
    if (size_t index = d_argConfig.option(opt))
    {
        for (; index--; )
        {
            string field;
            d_argConfig.option(index, &field, opt);
            dest.push_back(field);
        }
        return;
    }

    string configRE( R"(^\s*)" );
    (configRE += keyWord) += ":";

    Pattern pattern(configRE + R"(\s*(\S+))" );

    auto iters = d_argConfig.beginEndRE(configRE);
    for (auto &line: ranger(iters.first, iters.second))
    {
        if (pattern << line)
            dest.push_back(pattern[1]);
    }
            
    if (dest.size() == 0)
    {
        if (needElements)
            throw LogException() << "no `" << keyWord << 
                 "' specifications found in " << d_configName << '\n';
        return;
    }
    ostringstream out;
    copy(dest.begin(), dest.end(), ostream_iterator<string>(out, " "));
    d_log << level(LOGDEBUG) << keyWord << ": " << out.str() << '\n';
}



