#include "mail.ih"

vector<string> const &Mail::setRecipients(
                        string step, 
                        vector<string> &oneRecipient,
                        vector<string> const &configuredRecipients)
                                        
{
    size_t pos = step.find(':');    // explicit mail recipient?

    if (pos == string::npos)        // no, use provided recipient(s)
        return configuredRecipients;

                                    // yes: send the mail to that recipient
    oneRecipient.push_back(step.substr(pos + 1)); 

    d_log << level(LOGDEFAULT) << "Ignoring recipients, mail sent to " <<
                                  oneRecipient.front() << '\n';

    return oneRecipient;
}
