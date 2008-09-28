#include "remailer.ih"

void Remailer::setLog()
{
    string name;
    if (!d_arg.option(&name, 'l'))
        name = configField("logFile");

    if (name.empty())
        name = "etc/remailer.log";

    string level;
    if (!d_arg.option(&level, 'L'))
        level = configField("logLevel");

    if (level.empty())
        level = LOGDEFAULT;

    d_log.open(name);
    d_log.setLevel(A2x(level));
}
