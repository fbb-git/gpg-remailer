#include "mailerbase.ih"

// static
string MailerBase::cleanupHeader(string const &hdr)
{
    string header{hdr};

    while (true)
    {
        size_t pos0 = header.find('\n');        // any newline? 
        if (pos0 == string::npos)               // no: done
            break;
                                                // pos. of 1st non-blank 
                                                // beyond the \n
        size_t pos1 = header.find_first_not_of(" \t\n", pos0);

                        // e.g. 'n x': pos0 = 0, pos1 = 2 -> erase 1 char
        header.erase(pos0, pos1 - pos0 - 1);
        header[pos0] = ' ';
    }

    return R"( -a ")" + String::escape(header) + '"';
}
