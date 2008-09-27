#include "remailer.ih"

void Remailer::preparations()
{
    d_user.verify();

    msg() << "Current user: " << d_user.name() << " (" << d_user.userid() << 
                                                                ')' << info;
    if (chdir(d_user.homedir().c_str()) != 0)
        throw Errno();

    d_config.open(d_configName);

    setFilenames();                         // define all used filenames 
    multiField(d_members, "member");
    multiField(d_recipients, "recipient");

    string signatureRequired = configField("^\\s*signature:");

    ConfigFile::const_iterator iter = d_config.findRE("^\\s*replyTo:");
    if (iter != d_config.end())
    {
        d_replyTo = String::trim(*iter);
        d_replyTo = String::trim(
                        d_replyTo.substr(d_replyTo.find_first_of(" \t")));

        rmQuotes(d_replyTo);
    }
    if (d_replyTo.length() == 0)
        throw Errno(1, "Missing replyTo specification in config file");

    d_sigRequired = 
        signatureRequired == "good"     ? GOOD_SIGNATURE :
        signatureRequired == "required" ? SIGNATURE_FOUND :
                                          NO_SIGNATURE;
}
