#include "remailer.ih"

void Remailer::gpg(string command, string const &err)
{
    command = "/usr/bin/gpg  --quiet --batch "
                    "--homedir " + d_user.homedir() + ".gnupg " +
                    d_gpgOptions + ' ' + command;

    d_log << level(LOGCOMMANDS) << command << " 2>> " << err << '\n';

    Spawn gpg(command, "/dev/null", "/dev/null", err);
    gpg.fork();

}








