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


//    ofstream reencrypted;
//    ofopen(d_reencryptedName, &reencrypted);
//
//    ofstrteam err;
//    ofopen(d_errName, &err);
//
//    command << R"(" -r members)" <<
//            " < " << d_reencryptName << 
//            " >> " << d_reencryptedName << 
//            " 2>> " << d_errName;
//
//    gpg(command.str());
}



