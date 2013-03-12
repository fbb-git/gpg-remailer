#include "remailer.ih"

void Remailer::writeReencrypted()
{
    if (!step("enc"))
        return;

    ostringstream command;
    
    command << "--trust-model always --armor --encrypt --sign "
               "--group members=\"";

    copy(d_members.begin(), d_members.end(), 
            ostream_iterator<string>(command, " "));

    ofopen(d_reencryptedName);
    ofopen(d_errName);

    command << "\" -r members" <<
            " < " << d_reencryptName << 
            " >> " << d_reencryptedName << 
            " 2>> " << d_errName;

    gpg(command.str());
}
