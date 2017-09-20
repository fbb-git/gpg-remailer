#include "remailer.ih"

void Remailer::setKeepFiles()
{
    d_keepFiles = d_argConfig.option(&d_nr, 'n');     // determine predef'd filenr
    if (!d_keepFiles)                           // try fm config file
    {
        d_nr = configField("keepfiles");
        d_keepFiles = d_nr.length() > 0;
    }
}
