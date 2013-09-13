#include "remailer.ih"

void Remailer::gpg(string const &command, string const &err)
{
    ofstream errStream;
    open(errStream, err, UNLINK);
    
    Process process("/usr/bin/gpg  --quiet --batch "
                    "--homedir " + d_user.homedir() + ".gnupg " +
                    d_gpgOptions + ' ' + command);

    d_log << level(LOGCOMMANDS) << process.str() << " 2>> " << err << '\n';

    process.start();

    thread errThread(collect, &errStream, &process.cerr());

    errThread.join();

    process.waitForChild();
}








