#include "remailer.ih"

        // writes reencrypted.x and err.x (should be empty)
void Remailer::writeReencrypted()
{
    if (not (d_mailType == ENCRYPTED || step("enc")))
        return;

    string members;
    
    for(auto &member: d_members)
        members += member + ' ';

    d_gpg.encrypt(members, d_reencryptName, d_reencryptedName, d_errName);
}



