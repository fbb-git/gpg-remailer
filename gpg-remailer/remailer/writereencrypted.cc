#include "remailer.ih"

        // writes reencrypted.x and err.x (should be empty)
void Remailer::writeReencrypted()
{
    if (not (step("enc") || d_mailType == ENCRYPTED))
        return;

    string members;
    
    for(auto &member: d_members)
        members += member + ' ';

    d_gpg.encrypt(command, d_reencryptName, d_reencryptedName, d_errName);
}



