#include "remailer.ih"

bool Remailer::multipartSigned()
{
    ifstream in;
    Msg::open(in, d_decryptedName);

    string line;
    getline(in, line);              // does this line contains multipart/signed
        
    if (line.find("Content-Type: multipart/signed;") != 0)
        return false;               // no, it doesn't

    // It does: find the boundary
    while (!(d_bdry << line))
    {
        if (!getline(in, line))
            throw Errno(1, "multipart/signed: no boundary found");
    }

    // found the boundary
    string boundary = "--" + d_bdry[1];

    d_log << level(LOGDEBUG) << "Using boundary " << boundary << 
                " in multipart/signed message\n";

                                    // skip until the contents section
    while (getline(in, line) && line.find(boundary) != 0)
        ;
    
    if (!in)
        throw Errno(1, "multipart/signed: no boundary separator found");
    
    copyTo(d_multipartSigned, in, boundary);
    copyTo(d_detachedSignature, in, boundary);

    ostringstream command;

    ofopen(d_decryptedName);
    ofopen(d_signatureName);    

    command << "--verify " << 
            d_detachedSignature << " " << d_multipartSigned;
    
    gpg(command.str());
    return true;
}
