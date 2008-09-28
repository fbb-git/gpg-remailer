#include "remailer.ih"

void Remailer::preparations()
{
    d_user.verify();

    if (chdir(d_user.homedir().c_str()) != 0)   // change Homedir
        throw Errno();

    d_config.open(d_configName);                // prepare configuration file
                                                // MUST be following change to
                                                // the user's homedir

    setLog();                                   // define logging
    
    d_keepFiles = d_arg.option(&d_nr, 'n');     // determine predef'd filenr
    if (!d_keepFiles)                           // try fm config file
    {
        d_nr = configField("keepfiles");
        d_keepFiles = d_nr.length() > 0;
    }

    if (d_arg.option('d') || configField("debug") == "true")
    {
        d_keepFiles = true;
        d_log.setLevel(LOGDEBUG);
    }
    else
        d_gpgOptions = "--quiet --batch";

    d_log << level(LOGDEBUG) << 
        "User: " << d_user.name() << " (" << d_user.userid() << ")\n";

    setFilenames();                         // define all used filenames 

    multiField(d_members, "member");
    multiField(d_recipients, "recipient");

    string signatureRequired = configField("signature");

    ConfigFile::const_iterator iter = d_config.findRE("^\\s*replyTo:");
    if (iter != d_config.end())
    {
        d_replyTo = String::trim(*iter);
        d_replyTo = String::trim(
                        d_replyTo.substr(d_replyTo.find_first_of(" \t")));

        rmQuotes(d_replyTo);
    }
    if (d_replyTo.empty())
        throw Errno(1, "Missing replyTo specification in config file");

    d_sigRequired = 
        signatureRequired == "good"     ? GOOD_SIGNATURE :
        signatureRequired == "required" ? SIGNATURE_FOUND :
                                          NO_SIGNATURE;
}

