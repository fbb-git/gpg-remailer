#include "remailer.ih"

void Remailer::setUmask()
{
    string umaskOpt;
    size_t umaskValue = 077;
    if (d_argConfig.option(&umaskOpt, "umask"))
    {
        umaskValue = strToUnsigned(umaskOpt, "umask", 8);
        d_log << level(LOGDEFAULT) << "WARNING: umask setting changed to " <<
            oct << setfill('0') << setw(3) << umaskValue << 
            dec << setfill(' ') << '\n';
    }
    umask(umaskValue);
}
