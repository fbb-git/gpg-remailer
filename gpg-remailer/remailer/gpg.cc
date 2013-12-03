#include "remailer.ih"

void Remailer::gpg(string command, string const &in, string const &out,
                   string const &err)
{
    command = 
        "/usr/bin/gpg --quiet --batch "
        "--homedir " + d_user.homedir() + ".gnupg " +
        d_gpgOptions + ' ' + command;

    d_log << level(LOGCOMMANDS) << command << 
            " < " << in <<
            " > " << out <<
            " 2> " << err <<
            '\n';

    Spawn gpg(d_log, command, in, out, err);
    gpg.fork();
}








