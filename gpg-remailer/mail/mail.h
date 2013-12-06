#ifndef INCLUDED_MAIL_
#define INCLUDED_MAIL_

#include <string>

namespace FBB
{
    class ArgConfig;
    class Log;
};

class Mail
{
    FBB::ArgConfig &d_arg;
    FBB::Log  &d_log;
    FBB::MailHeaders d_headers;

    public:
        Mail();
        void writeHeaders(std::string const &hdrsName);
        void writeContents(std::string const &hdrsName);

    private:
        bool PGPmessage(std::ostream &out);
        void filter(std::ostream &out);
        void inspect(std::ostream &out, std::string const &line);
        void hexChar(std::ostream &out, std::istream &in);
};
        
#endif
