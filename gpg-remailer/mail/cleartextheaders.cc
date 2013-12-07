#include "mail.ih"

string Mail::clearTextHeaders()
{
    string mime = getHeader("MIME-Version");

    d_headers.setHeaderIterator("Content-", MailHeaders::INITIAL);

    string contentHdr;

    if (not mime.empty())
        contentHdr = R"(-a ")" + String::escape(mime) + '"';

    for 
    (
        auto begin = d_headers.beginh(), end = d_headers.endh();
            begin != end;
                ++begin
    )
    {
        string header(*begin);
        if (
            header.find("Content-Type") == 0 
            ||
            header.find("Content-Disposition") == 0
        )
        {
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
            contentHdr += R"( -a ")" + String::escape(header) + '"';
        }
    }
    return contentHdr;
}
