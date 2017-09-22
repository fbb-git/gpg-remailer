#ifndef INCLUDED_MAILER_
#define INCLUDED_MAILER_

#include "../mailerbase/mailerbase.h"

template <class Derived>
class Mailer: private MailerBase
{
    public:
        Mailer(FBB::Log &log, Headers &headers, 
               std::string const &mailName,
               std::string const &step);

        void send(std::string const &mailData, 
                    std::vector<std::string> const &recipients,
                    bool dontSend);

    protected:
        typedef Mailer<Derived> MailerFriend;

        using MailerBase::subject;
        using MailerBase::headers;

    private:
    // Derived classes must implement and allow the following members
    // to be callled from MailerFriend::send:
    //
    //      void writeMailContents(std::string const &mailData) const;
    //      std::string mailCommand(std::string const &recipients) 
    //      std::string label() const;
};
        
#include "mailer1.f"
#include "send.f"

#endif






