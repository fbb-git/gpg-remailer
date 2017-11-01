#include "mailerbase.ih"

// static
bool MailerBase::contentHeader(char const *headerCp)
{
    return                           // either of these headers encountered
        strcasestr(headerCp, "Content-Type") == headerCp
        ||
        strcasestr(headerCp, "Content-Disposition") == headerCp;
}
