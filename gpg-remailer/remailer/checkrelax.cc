#include "remailer.ih"

void Remailer::checkRelax()
{
    if (d_argConfig.option(0, "relax"))
        d_log << level(LOGDEFAULT) << 
                "--relax ignored. Use `--umask' instead\n";
}
