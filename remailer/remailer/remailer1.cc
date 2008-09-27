#include "remailer.ih"

Remailer::Remailer()
:
    d_arg(Arg::instance()),
    d_config(ConfigFile::RemoveComment)
{
    if (d_arg.option('d'))
        Msg::setDisplay(true);
    else
        d_gpgOptions = "--quiet --batch";

    d_arg.option(&d_step, "step");

    d_configName = d_arg.nArgs() == 0 ? "etc/remailer.rc" : d_arg[0];
}
