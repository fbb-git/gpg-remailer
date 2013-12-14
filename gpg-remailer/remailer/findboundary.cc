#include "remailer.ih"

void Remailer::findBoundary(IOContext &io)
{
    while (!hasBoundary(io.line, "multipart/signed"))
    {
        if (!getline(io.decrypted, io.line))
            throw LogException() << 
                    "multipart/signed: no boundary found\n";
    }
}
