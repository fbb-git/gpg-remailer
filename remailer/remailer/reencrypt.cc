#include "remailer.ih"

void Remailer::reencrypt()
{
    fileToReencrypt();          // requires step 'doc'
    writeReencrypted();         // requires step 'enc'
}
