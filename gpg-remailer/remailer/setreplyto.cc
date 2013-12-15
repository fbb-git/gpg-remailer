#include "remailer.ih"

void Remailer::setReplyTo()
{
    ConfigFile::const_iterator iter = d_config.findRE(R"(^\s*replyTo:)");
    if (iter != d_config.end())
    {
        d_replyTo = String::trim(*iter);
        d_replyTo = String::trim(
                        d_replyTo.substr(d_replyTo.find_first_of(" \t")));
        d_replyTo = String::escape(d_replyTo);
    }
    if (d_replyTo.empty())
        throw LogException() << 
                    "Missing `replyTo' specification in config file";
}

