#include "remailer.ih"

    // Third format mentioned in the man-page
void Remailer::multipartSigned(ostream &toReencrypt, istream &in)
{
    copyToBoundary(d_multipartSignedDataName, in);
    copyToBoundary(d_multipartSignedSignatureName, in);

    ostringstream command;
    command << "--verify " << 
            d_multipartSignedDataName << " " << 
            d_multipartSignedSignatureName << " 2> " << d_signatureName;
    gpg(command.str());


    signatureSection(out, d_boundary);

    ifstream data;
    Msg::open(data, d_multipartSignedDataName);
    cout << "Processing the multipart signed section " << 
            d_multipartSignedDataName << "\n";

    out << data.rdbuf();

    return true;
}

