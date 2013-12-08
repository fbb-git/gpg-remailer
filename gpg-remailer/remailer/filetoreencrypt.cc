#include "remailer.ih"

    // writes reencrypt.x

void Remailer::fileToReencrypt()
{
    if (not (d_mailType == ENCRYPTED || step("doc")))
        return;

    IOContext io;

    IO::unlink(d_reencryptName);
    IO::open(io.toReencrypt, d_reencryptName, d_relax);

    Exception::open(io.decrypted, d_decryptedName);

                        // write the file to reencrypt as 
                        //  - a simple one-piece text (simple.cc)
                        //  - text consisting of multiple parts (multipart.cc)
                        //  - text consisting of multiple parts and a detached
                        //    signature (multipartsigned.cc)
    (this->*s_reEncrypt[ encryptionType(io) ])(io);
}


