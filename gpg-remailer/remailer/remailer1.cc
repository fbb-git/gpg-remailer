#include "remailer.ih"

Remailer::Remailer(Preamble const &preamble)
:
    d_preamble(preamble),
    d_keepFiles(false),
    d_config(preamble.configName,
             ConfigFile::RemoveComment, ConfigFile::SearchCaseInsensitive),
    d_mail(d_log, d_headers, d_mailName, d_replyTo, d_step, d_recipients),
    d_gpg(d_log, preamble.user.homedir())
{
    d_preamble.arg.option(&d_step, "step");

    if (preamble.arg.option('x') || not d_config.find("x-headers")->empty())
        d_headers.fillXheaders();

    setLog();                                   // define logging
}



