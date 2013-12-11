#ifndef INCLUDED_HEADERS_
#define INCLUDED_HEADERS_

#include <bobcat/mailheaders>

class Headers: public FBB::MailHeaders
{
    public:
        Headers();

        const_hdr_iterator mailHeader(char const *hdr);
        std::string getHeader(char const *hdr);

    private:
};
        
#endif
