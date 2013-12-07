#include "mail.ih"

void Mail::sendClearTextMail(string const &recipient)
{
    sendMail(clearTextMailCommand(recipient), "Clear text mail", recipient);
}




