#include "remailer.ih"

void Remailer::reencrypt()
{
    fileToReencrypt();          // requires step 'doc'. Writes reencrypt.x and
                                //  maybe multipartsigned.x

    writeReencrypted();         // requires step 'enc'. Writes reencrypted.x
}
