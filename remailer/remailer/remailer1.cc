#include "remailer.ih"

Remailer::Remailer()
:
    d_arg(Arg::instance()),
    d_config(ConfigFile::RemoveComment, ConfigFile::SearchCaseInsensitive),
    d_keepFiles(false)
{
    d_arg.option(&d_step, "step");

    d_configName = d_arg.nArgs() == 0 ? "etc/remailer.rc" : d_arg[0];
}
