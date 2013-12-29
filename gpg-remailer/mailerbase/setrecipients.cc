#include "mailerbase.ih"

vector<string> const &MailerBase::setRecipients(
                        vector<string> &oneRecipient,
                        vector<string> const &configuredRecipients)
                                        
{
    size_t pos = d_step.find(':');    // explicit mail recipient?

    if (pos == string::npos)        // no, use provided recipient(s)
        return configuredRecipients;

                                    // yes: send the mail to that recipient
    oneRecipient.push_back(d_step.substr(pos + 1)); 

    d_log << FBB::level(LOGDEFAULT) << "Ignoring recipients, mail sent to " <<
                                  oneRecipient.front() << '\n';

    return oneRecipient;
}
