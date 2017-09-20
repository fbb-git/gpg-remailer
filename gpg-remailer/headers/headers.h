#ifndef INCLUDED_HEADERS_
#define INCLUDED_HEADERS_

#include <string>

#include <bobcat/mailheaders>

class Headers: public FBB::MailHeaders
{
    std::string d_xHeaders;

    public:
        Headers();

        const_hdr_iterator mailHeader(char const *hdr);
        std::string getHeader(char const *hdr);
        std::string const &xHeaders() const;
    private:
        void fillXheaders();
};
        
inline std::string const &Headers::xHeaders() const
{
    return d_xHeaders;
}

#endif

