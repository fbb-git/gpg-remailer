#include "remailer.ih"

bool Remailer::findBoundary(istream &in)
{
    string line;
    getline(in, line);          // does this line contains multipart/signed
        
    if (line.find("Content-Type: multipart/signed;") != 0)
        return false;           // no, it doesn't

    while (!hasBoundary(line, "multipart/signed"))
    {
        if (!getline(in, line))
            msg() << "multipart/signed: no boundary found" << fatal;
    }

    return true;    
}
