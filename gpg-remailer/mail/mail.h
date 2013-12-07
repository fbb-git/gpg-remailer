#ifndef INCLUDED_MAIL_
#define INCLUDED_MAIL_

#include <string>
#include <vector>

#include <bobcat/mailheaders>
#include "../enums/enums.h"

namespace FBB
{
    class Log;
};

class Mail: private Enums
{
    FBB::Log  &d_log;
    FBB::MailHeaders d_headers;
    bool d_relax;
    bool d_clearTextAccepted = false;

    std::string d_subject;
    std::string const *d_mailNamePtr;
    std::string const *d_replyToPtr;
    bool d_dontSend = true;

    public:
        Mail(FBB::Log &log, bool relax);
        void writeHeaders(std::string const &hdrsName);
        MailType writeContents(std::string const &hdrsName);
        void operator()(MailType type, 
                        std::string const &contents,
                        std::string const &mailName,
                        std::string const &replyTo,
                        std::string const &step,
                        std::vector<std::string> const &recipients,
                        bool dontSend);

        void setClearTextMode(ClearText mode);

    private:
        bool PGPmessage(std::ostream &out);
        void filter(std::ostream &out);
        void inspect(std::ostream &out, std::string const &line);
        void hexChar(std::ostream &out, std::istream &in);

        FBB::MailHeaders::const_hdr_iterator mailHeader(char const *hdr);
        std::string getHeader(char const *hdr);

        std::vector<std::string> const &setRecipients(
                        std::string step, 
                        std::vector<std::string> &oneRecipient,
                        std::vector<std::string> const &configuredRecipients
        );

        void sendMail(
                        std::string const &command, 
                        std::string const &label, 
                        std::string const &recipient
        );

        std::string clearTextHeaders();
        std::string clearTextMailCommand(std::string const &recipient);
        void sendClearTextMail( 
                        std::string const &recipient
        );
        void clearTextMail(
                        std::string const &org,
                        std::vector<std::string> const &recipients
        );

        std::string makePGPBoundary();
        void writePGPmail(
                        std::string const &reencrypted,
                        std::string const &boundary
        );
        std::string pgpMailCommand(
                        std::string const &recipient, 
                        std::string const &boundary
        );
        void sendPGPmail(
                        std::string const &recipient,
                        std::string const &boundary
        );
        void pgpMail(
                        std::string const &reencrypted,
                        std::vector<std::string> const &recipients
        );
};

inline void Mail::setClearTextMode(ClearText mode)
{
    d_clearTextAccepted = mode == ACCEPTED;
}
        
#endif





