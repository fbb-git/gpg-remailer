#include "remailer.ih"

void Remailer::checkRelax()
{
    if (d_preamble.arg.option(0, "relax"))
        d_log << level(LOGDEFAULT) << 
                "--relax ignored. Use `--umask' instead\n";
}
