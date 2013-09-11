#include "remailer.ih"

void Remailer::writeReencrypted()
{
    if (!step("enc"))
        return;

    ostringstream command;
    
    command << "--trust-model always --armor --encrypt --sign "
               R"(--group members=")";

    copy(d_members.begin(), d_members.end(), 
            ostream_iterator<string>(command, " "));

    command << R"(" -r members)";

    gpg(command.str(), d_reencryptName, d_reencryptedName, d_errName);
}



