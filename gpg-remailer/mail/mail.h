#ifndef INCLUDED_MAIL_
#define INCLUDED_MAIL_

#include <string>
#include <vector>

#include "../enums/enums.h"

namespace FBB
{
    class Log;
};

class Headers;

class Mail: private Enums
{
    FBB::Log  &d_log;
    Headers &d_headers;
    std::string const &d_mailName;
    std::string const &d_replyTo;
    std::string const &d_step;

    bool d_clearTextAccepted = false;

    std::string d_subject;
    bool d_dontSend = true;
    std::vector<std::string> const &d_recipients;

    public:
        Mail(FBB::Log &log, Headers &headers, std::string const &mailName,
                std::string const &replyTo, std::string const &step,
                std::vector<std::string> const &recipients);
        void writeHeaders(std::string const &hdrsName);
        MailType writeContents(std::string const &hdrsName);
        void operator()(MailType type, 
                        std::string const &mailData,
                        bool dontSend);

        void setClearTextMode(ClearText mode);

    private:
        template <class Mailer>
        void mail(std::string const &mailData, bool dontSend, 
                  Mailer &&mailer);

        bool PGPmessage(std::ostream &out);
        void filter(std::ostream &out);
        void inspect(std::ostream &out, std::string const &line);
        void hexChar(std::ostream &out, std::istream &in);
};

template <class Mailer>
inline void Mail::mail(std::string const &mailData, bool dontSend, 
                       Mailer &&mailer)
{
    mailer.send(mailData, d_recipients, dontSend);
}

inline void Mail::setClearTextMode(ClearText mode)
{
    d_clearTextAccepted = mode == ACCEPTED;
}
        
#endif





