#ifndef INCLUDED_CLEARTEXTMAIL_
#define INCLUDED_CLEARTEXTMAIL_

namespace FBB
{
    class Log;
}

#include "../mailer/mailer.h"

class Headers;

class ClearTextMail: public Mailer<ClearTextMail>
{
    friend void MailerFriend::send(std::string const &mailData, 
                    std::vector<std::string> const &recipients,
                    bool dontSend);

    Headers &d_headers;
    std::string const &d_mailName;
    std::string const &d_replyTo;

    public:
        ClearTextMail(FBB::Log &log, Headers &headers, 
                        std::string const &mailName,
                        std::string const &replyTo,
                        std::string const &step
        );

    private:
            // Called through MailerBase:
        std::string label() const;
        std::string mailCommand(std::string const &recipient) const;
        void writeMailContents(std::string const &mailData) const;
};
        
#endif


