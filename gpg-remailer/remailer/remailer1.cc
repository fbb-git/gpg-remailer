#include "remailer.ih"

Remailer::Remailer(void (*usage)(std::string const &),
                   char const *options, 
                   ArgConfig::LongOption const *const longOptions, 
                   ArgConfig::LongOption const *const longEnd, 
                   int argc, char **argv)
:
    d_argConfig(
        ArgConfig::initialize(options, longOptions,longEnd, argc, argv,
                              ArgConfig::RemoveComment, 
                              ArgConfig::SearchCaseInsensitive)
    ),
    d_keepFiles(false),
    d_mail(d_log, d_headers, d_mailName, d_replyTo, d_step, d_recipients),
    d_gpg(d_log, d_user.homedir())
{
    d_argConfig.option(&d_step, "step");

    d_configName = d_argConfig.nArgs() == 0 ? 
                        "etc/gpg-remailer.rc" 
                    : 
                        d_argConfig[0];

    if (chdir(d_user.homedir().c_str()) != 0)   // change Homedir
        throw Exception() << "Failed to change dir to " << d_user.homedir();

    d_argConfig.open(d_configName);             // prepare configuration file
                                                // MUST be following change to
                                                // the user's homedir

    d_argConfig.versionHelp(usage, version, 0);

    setLog();                                   // define logging
}



