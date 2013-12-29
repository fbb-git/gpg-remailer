#ifndef INCLUDED_MAILERBASE_
#define INCLUDED_MAILERBASE_

#include <string>
#include <vector>

class Headers;

namespace FBB
{
    class Log;
}

#include "../enums/enums.h"

class MailerBase: Enums
{
    FBB::Log &d_log;
    Headers &d_headers;
    std::string const &d_mailName;
    std::string const &d_step;
    std::string d_subject;

    protected:
        MailerBase(FBB::Log &log, Headers &headers, 
               std::string const &mailName,
               std::string const &step);

        std::vector<std::string> const &setRecipients(
                        std::vector<std::string> &oneRecipient,
                        std::vector<std::string> const &configuredRecipients
        );

        std::string const &subject() const;

        void sendMail(std::string const &command, std::string const &label, 
                      std::string const &recipient, bool dontSend);
};
        
inline std::string const &MailerBase::subject() const
{
    return d_subject;
}

#endif
