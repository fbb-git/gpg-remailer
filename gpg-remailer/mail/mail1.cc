#include "mail.ih"

Mail::Mail(Log &log, bool relax)
:
    d_log(log),
    d_headers(cin),
    d_relax(relax)
{
}
