#include "remailer.ih"

void Remailer::mailContents()
{
    if (!step("org"))
        return;
                                        // explicit steps may be used to 
                                        // process a particular type of mail,
                                        // even if 'org' wasn't used.
    d_mailType = d_mail.writeContents(d_contentsName);
}
