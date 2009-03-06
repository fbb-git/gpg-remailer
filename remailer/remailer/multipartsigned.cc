#include "remailer.ih"

    // Third format mentioned in the man-page
void Remailer::multipartSigned(IOContext &io)
{
    findBoundary(io.decrypted);

    ostream null(0);
    copyToBoundary(null, io.decrypted);           // skip all headers

    copyToBoundary(d_multipartSignedDataName, io.decrypted);

    ostringstream command;
    command << "--verify " << 
            d_decryptedName << " " << d_multipartSignedDataName << 
            " 2> " << d_signatureName;
    gpg(command.str());

    copySignature(io.toReencrypt, d_boundary);

    ifstream data;
    Msg::open(data, d_multipartSignedDataName);

    io.toReencrypt << data.rdbuf();
}


