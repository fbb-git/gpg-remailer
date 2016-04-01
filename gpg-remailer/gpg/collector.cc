#include "gpg.ih"

// static
void GPG::collector(char const *out, streambuf *buffer)
{
    ofstream outStream;
    Exception::open(outStream, out);
    outStream << buffer << flush;
}
