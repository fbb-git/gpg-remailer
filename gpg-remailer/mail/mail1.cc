#include "mail.ih"

Mail::Mail(Log &log)
:
    d_arg(ArgConfig::instance()),
    d_log(log),
    d_mailHeaders(cin)
{
}
