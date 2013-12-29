template <class Derived>
void Mailer<Derived>::send(std::string const &mailData, 
                       std::vector<std::string> const &configuredRecipients, 
                       bool dontSend)
{
    static_cast<Derived *>(this)->writeMailContents(mailData);

    std::vector<std::string> oneRecipient;

    std::vector<std::string> const &recipients = 
                setRecipients(oneRecipient, configuredRecipients);

    std::string logLabel = static_cast<Derived *>(this)->label();

    for (auto &recipient: recipients)
        sendMail(static_cast<Derived *>(this)->mailCommand(recipient), 
                 logLabel, recipient, dontSend);
}
