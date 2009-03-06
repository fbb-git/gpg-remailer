#include "remailer.ih"

void Remailer::multipart(IOContext &io)
{
    io.toReencrypt << io.line << endl;  // line containing 
                                        // Content-Type: multipart

    copyToBoundary(io.toReencrypt, io.decrypted);
    copySignature(io.toReencrypt, d_boundary);
    io.toReencrypt << io.decrypted.rdbuf();
}
