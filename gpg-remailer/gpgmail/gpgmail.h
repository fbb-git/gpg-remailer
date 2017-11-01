#ifndef INCLUDED_GPGMAIL_
#define INCLUDED_GPGMAIL_

#include <string>

#include "../mailer/mailer.h"

namespace FBB
{
    class Log;
}

class Headers;

class GPGMail: public Mailer<GPGMail>
{
    friend void MailerFriend::send(std::string const &mailData, 
                    std::vector<std::string> const &recipients,
                    bool dontSend);

    std::string const &d_mailName;
    std::string const &d_replyTo;
    std::string d_boundary;

    public:
        GPGMail(FBB::Log &log, Headers &headers, 
                std::string const &mailName, std::string const &replyTo,
                std::string const &step);

    private:
        static std::string makeBoundary();

            // Called through MailerBase:
        void writeMailContents(std::string const &mailData) const;
        std::string mailCommand(std::string const &recipients) const;
        std::string label() const;

        static void processHeaders(std::string &contentHdr, 
                                   std::string const &hdr);
};
        
#endif




