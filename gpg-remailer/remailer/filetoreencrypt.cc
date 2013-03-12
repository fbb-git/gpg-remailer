#include "remailer.ih"

void Remailer::fileToReencrypt()
{
    if (!step("doc"))
        return;

    IOContext io;

    ofopen(d_reencryptName, &io.toReencrypt);
    Exception::open(io.decrypted, d_decryptedName);

    (this->*s_reEncrypt[ encryptionType(io) ])(io);
}


