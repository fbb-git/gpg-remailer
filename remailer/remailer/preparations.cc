#include "remailer.ih"

void Remailer::preparations()
{
    d_user.verify();

    if (chdir(d_user.homedir().c_str()) != 0)   // change Homedir
        throw Errno(1, "Failed to change dir to ") << insertable <<
                                            d_user.homedir() << throwable;

    d_config.open(d_configName);                // prepare configuration file
                                                // MUST be following change to
                                                // the user's homedir

    setLog();                                   // define logging

    if (d_relax)
        d_log << level(LOGDEFAULT) << "WARNING: relaxed permission tests\n";

    testPermissions(d_user.homedir());
    testPermissions(d_configName, Stat::UR | Stat::UW);
    
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

    multiField(d_members, "member", 'm');
    multiField(d_recipients, "recipient", 'r');

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
        d_log << level(LOGDEFAULT) << 
            "Missing `replyTo' specification in config file" << FATAL;

    d_sigRequired = 
        signatureRequired == "good"     ? GOOD_SIGNATURE :
        signatureRequired == "required" ? SIGNATURE_FOUND :
                                          NO_SIGNATURE;
}

