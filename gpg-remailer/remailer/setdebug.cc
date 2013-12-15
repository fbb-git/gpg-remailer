#include "remailer.ih"

void Remailer::setDebug()
{
    if (d_arg.option('d') || configField("debug") == "true")
    {
        d_keepFiles = true;
        d_log.setLevel(LOGDEBUG);
        d_gpg.debug();
    }
}
