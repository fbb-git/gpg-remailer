#include "mailerbase.ih"

string MailerBase::headers(
                    void  (*processHeaders)(string &, string const &)
                          ) const
{
    string mime = d_headers.getHeader("MIME-Version");

    string contentHdr{ d_headers.xHeaders() };  // get the X-GPG-remailer
                                                // headers

    if (not mime.empty())                       // add the mime-version
        contentHdr += R"( -a ")" + String::escape(mime) + '"';

                                                // look for the Content- hdrs
    d_headers.setHeaderIterator("Content-", MailHeaders::CASE_INITIAL);

    for                                         // visit them all
    (
        auto begin = d_headers.beginh(), end = d_headers.endh();
            begin != end;
                ++begin
    )
        (*processHeaders) (contentHdr, *begin);


    return contentHdr;
}

