#include "mailerbase.ih"

string MailerBase::headers() const
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
    {
        string header(*begin);
        char const *headerCp = header.c_str();

        if (                                    // at either of these headers
            strcasestr(headerCp, "Content-Type") == headerCp
            ||
            strcasestr(headerCp, "Content-Disposition") == headerCp
        )
            continue;                           // skip them (they contain
                                                // the orig. boundary)

        while (true)
        {
            size_t pos0 = header.find('\n');    // any newline? 
            if (pos0 == string::npos)           // no: done
                break;
                                                // pos. of 1st non-blank 
                                                // beyond the \n
            size_t pos1 = header.find_first_not_of(" \t\n", pos0);

                // e.g. 'n x': pos0 = 0, pos1 = 2 -> erase 1 char
            header.erase(pos0, pos1 - pos0 - 1);
            header[pos0] = ' ';
        }
                                                // add the encountered header
                                                // to the reencrypted mail
        contentHdr += R"( -a ")" + String::escape(header) + '"';
        
    }
    return contentHdr;
}

