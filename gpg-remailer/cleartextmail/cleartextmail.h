#ifndef INCLUDED_CLEARTEXTMAIL_
#define INCLUDED_CLEARTEXTMAIL_

#include <iosfwd>

class ClearTextMail
{
    std::string const &d_mailSource;
    MailHeaders &d_headers;

    public:
        ClearTextMail(Headers &headers, std::string const &mailSource);

    private:
        std::string headers();

        void writeMailContents(std::string const &destination) override;
};
        
#endif
