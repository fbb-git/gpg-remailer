#include "remailer.ih"

string Remailer::makePGPBoundary()
{
    string boundary;

    if (d_mailType != ENCRYPTED)
        return boundary;

    IRandStream rs(' ' + 1, '~', time(0));

    for (int idx = 0; idx != 16; ++idx)
    {
        while (true)
        {
            size_t value;
            rs >> value;
            if (isalnum(value))
            {
                boundary += static_cast<char>(value);
                break;
            }
        }
    }      
    return boundary;
}
