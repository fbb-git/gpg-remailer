#include "remailer.ih"

void Remailer::fileToReencrypt()
{
    if (!step("doc"))
        return;

    ofstream toReencrypt;
    ofopen(d_reencryptName, &toReencrypt);

    ifstream in;
    Msg::open(in, d_decryptedName);

    (this->*s_reEncrypt[encryptionType(toReencrypt, in)])(toReencrypt, in);
}


