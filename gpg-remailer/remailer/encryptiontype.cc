#include "remailer.ih"

Remailer::EncryptionEnum Remailer::encryptionType(IOContext &io)
{
    getline(io.decrypted, io.line);              
                                // does this line contains multipart/signed ?
    if (io.line.find("Content-Type: multipart/signed;") == 0)
        return MULTIPART_SIGNED;

    if (hasBoundary(io.line, "multipart"))
        return MULTIPART;

    d_log << level(LOGDEBUG) << "No boundary, no multipart message\n";

    return SIMPLE;    
}
