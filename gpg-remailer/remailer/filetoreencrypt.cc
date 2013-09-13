#include "remailer.ih"

void Remailer::fileToReencrypt()
{
    if (!step("doc"))
        return;

    IOContext io;

    open(io.toReencrypt, d_reencryptName, UNLINK);

    Exception::open(io.decrypted, d_decryptedName);

    (this->*s_reEncrypt[ encryptionType(io) ])(io);
}


