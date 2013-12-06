#include "remailer.ih"

void Remailer::mailContents()
{
    if (!step("org"))
        return;

    mail.writeContents(d_contentsName);
}
