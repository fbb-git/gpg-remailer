#include "remailer.ih"

        // writes reencrypted.x and err.x (should be empty)
void Remailer::writeReencrypted()
{
    if (!step("enc"))
        return;

    ostringstream command;
    
    command << R"(--trust-model always --armor --group members=")";

    copy(d_members.begin(), d_members.end(), 
            ostream_iterator<string>(command, " "));

    command << R"(" -r members --encrypt --sign )";

    gpg(command.str(), d_reencryptName, d_reencryptedName, d_errName);
}



