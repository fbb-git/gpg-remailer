#ifndef INCLUDED_MAILER_
#define INCLUDED_MAILER_

#include <string>
#include <vector>

#include "../enums/enums.h"
#include "../headers/headers.h"

namespace FBB
{
    class Log;
}

class Mailer: private Enums
{
    FBB::Log &d_log;
    Headers &d_headers;
    std::string const &d_mailName;
    std::string const &d_step;
    std::string d_subject;

    public:
        Mailer(FBB::Log &log, Headers &headers, 
               std::string const &mailName,
               std::string const &step);

        void send(std::string const &mailData, 
                    std::vector<std::string> const &recipients,
                    bool dontSend);

    protected:
        std::string const &subject() const;
        
    private:
        void sendMail(std::string const &command, std::string const &label, 
                      std::string const &recipient, bool dontSend);

        std::vector<std::string> const &setRecipients(
                        std::vector<std::string> &oneRecipient,
                        std::vector<std::string> const &configuredRecipients
        );

        virtual void writeMailContents(std::string const &mailData) const = 0;

        virtual std::string mailCommand(std::string const &recipients) 
                                                            const = 0; 
        virtual std::string label() const = 0;
};
        
inline std::string const &Mailer::subject() const
{
    return d_subject;
}

#endif






