#include "remailer.ih"

Remailer::Remailer()
:
    d_arg(Arg::instance()),
    d_keepFiles(false),
    d_relax(d_arg.option(0, "relax")),
    d_config(ConfigFile::RemoveComment, ConfigFile::SearchCaseInsensitive),
    d_mail(d_relax, d_log, d_step, d_replyTo, d_recipients, d_mailName),
    d_gpg(d_log, d_user.homedir())
{
    d_arg.option(&d_step, "step");

    d_configName = d_arg.nArgs() == 0 ? "etc/gpg-remailer.rc" : d_arg[0];

    if (chdir(d_user.homedir().c_str()) != 0)   // change Homedir
        throw Exception() << "Failed to change dir to " << d_user.homedir();

    d_config.open(d_configName);                // prepare configuration file
                                                // MUST be following change to
                                                // the user's homedir

    setLog();                                   // define logging
}
