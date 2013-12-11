#include "mailer.ih"

void Mailer::send(std::string const &mailData, 
                    vector<string> const &configuredRecipients, 
                    bool dontSend)
{
    writeMailContents(mailData);

    vector<string> oneRecipient;

    vector<string> const &recipients = 
                setRecipients(oneRecipient, configuredRecipients);

    string logLabel = label();

    for (auto &recipient: recipients)
        sendMail(mailCommand(recipient), logLabel, recipient, dontSend);
}
