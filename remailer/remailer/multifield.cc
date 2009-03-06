#include "remailer.ih"

void Remailer::addField(string const &line, FieldStruct &fs)
{
    if (fs.pattern << line)
        fs.dest.push_back(fs.pattern[1]);
}
    

void Remailer::multiField(vector<string> &dest, char const *keyWord, int opt)
{
    string field;
    if (d_arg.option(&field, opt))
    {
        dest.push_back(field);
        return;
    }

    string configRE("^\\s*");
    (configRE += keyWord) += ":";

    Pattern pattern(configRE + "\\s*(\\S+)");

    FieldStruct fs = {dest, pattern, configRE};

    for_each(d_config.beginRE(configRE), d_config.endRE(), 
            FnWrap1c<string const &, FieldStruct &>(addField, fs));

    if (dest.size() == 0)
        d_log << level(LOGDEFAULT) << "No `" << keyWord << 
                 "' specifications found in " << d_configName << FATAL;

    ostringstream out;
    copy(dest.begin(), dest.end(), ostream_iterator<string>(out, " "));
    d_log << level(LOGDEBUG) << keyWord << ": " << out.str() << '\n';
}
