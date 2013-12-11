#include "mailer.ih"

void Mailer::send(std::string contents, 
                  std::vector<std::string> const &recipients,
                  string subject)
{
    writeMailContents(d_mailName);

    string const &logLabel = label();

    for (auto &recipient: recipients)
        sendMail(mailCommand(recipient), logLabel, recipient, subject);
}
