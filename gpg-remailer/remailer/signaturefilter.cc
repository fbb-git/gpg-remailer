#include "remailer.ih"

void Remailer::signatureFilter(string const &line, SigStruct &sigStruct)
{
    if 
    (
        sigStruct.sigType == ABSENT && 
            line.find("Signature made") != string::npos
    )
        sigStruct.sigType = SIGNATURE_REQUIRED;
    else if (line.find("Good signature") != string::npos)
        sigStruct.sigType = GOOD_SIGNATURE;
    
    sigStruct.out << line << endl;
}
