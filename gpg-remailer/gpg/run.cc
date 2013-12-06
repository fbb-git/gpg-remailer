#include "gpg.ih"

void GPG::run(string command, string const &in, string const &out,
              string const &err)
{
    command = 
        "/usr/bin/gpg " + d_options + 
        " --homedir " + homedir + ".gnupg " + command;

    d_log << level(LOGCOMMANDS) << command << 
            " < " << in <<
            " > " << out <<
            " 2> " << err <<
            '\n';

    Spawn gpg(d_log, command, in, out, err);
    gpg.fork();
}








