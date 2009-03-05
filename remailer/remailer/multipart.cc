#include "remailer.ih"

void Remailer::multipart(ostream &toReencrypt, istream &in)
{
    copyToBoundary(toReencrypt, in);
    signatureSection(toReencrypt, d_boundary);  // copy the signature
    toReencrypt << in.rdbuf();                  // copy the remainder of `in'
}
