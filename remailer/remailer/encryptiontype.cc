#include "remailer.ih"

Remailer::EncryptionEnum Remailer::encryptionType(ostream &out, istream &in)
{
    Msg::open(in, d_decryptedName);

    string line;
    getline(in, line);              
                                // does this line contains multipart/signed ?
    if (line.find("Content-Type: multipart/signed;") != 0)
    {
        findBoundary(in);
        ostream null(0);
        copyToBoundary(null, in);

        return MULTIPART_SIGNED;
    }

    if (has_boundary(line, "multipart"))
    {
        out << line << endl;
        return MULTIPART;
    }

    d_log << level(LOGDEBUG) << "No boundary, no multipart message\n";
    return SIMPLE;    
}
