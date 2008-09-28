#include "remailer.ih"

void Remailer::gpg(string const &command)
{
    string gpgCmd = "/usr/bin/gpg "
                    "--homedir " + d_user.homedir() + ".gnupg " +
                    d_gpgOptions + ' ' + command;

    Process process(5, gpgCmd);

    d_log << level(LOGCOMMANDS) << gpgCmd << "\n";

    process.system();
    process.wait();
}
