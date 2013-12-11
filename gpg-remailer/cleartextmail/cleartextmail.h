#ifndef INCLUDED_CLEARTEXTMAIL_
#define INCLUDED_CLEARTEXTMAIL_

namespace FBB
{
    class Log;
}

#include "../mailer/mailer.h"

class ClearTextMail: public Mailer
{
    Headers &d_headers;
    std::string const &d_mailName;

    public:
        ClearTextMail(FBB::Log &log, Headers &headers, 
                        std::string const &mailName,
                        std::string const &replyTo,
                        std::string const &step
        );

    private:
        std::string headers() const;

        std::string label() const override;
        std::string mailCommand(std::string const &recipient) const override;
        void writeMailContents(std::string const &mailData) const override;
};
        
#endif

