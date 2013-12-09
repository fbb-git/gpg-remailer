#include "remailer.ih"

void Remailer::mailContents()
{
    if (not step("org"))
        return;
                                        // explicit steps may be used to 
                                        // process a particular type of mail,
                                        // even if 'org' wasn't used.
    MailType type = d_mail.writeContents(d_contentsName);

    if (d_step.empty())                 // mail type remains unknown for 
        d_mailType = type;              // specific step requests, to prevent
                                        // automatically sending mail.
}
