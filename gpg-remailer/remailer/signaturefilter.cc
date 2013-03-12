#include "remailer.ih"

void Remailer::signatureFilter(string const &line, SigStruct &sigStruct)
{
    if 
    (
        sigStruct.sigType == NO_SIGNATURE && 
            line.find("Signature made") != string::npos
    )
        sigStruct.sigType = SIGNATURE_FOUND;
    else if (line.find("Good signature") != string::npos)
        sigStruct.sigType = GOOD_SIGNATURE;
    
    sigStruct.out << line << endl;
}
