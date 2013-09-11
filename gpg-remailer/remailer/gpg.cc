#include "remailer.ih"

void Remailer::gpg(string const &command, string const &in, string const &out,
                   string const &err)
{
    ifstream inStream;
    Exception::open(inStream, in);

    ofstream outStream;
    open(outStream, out);

    ofstream errStream;
    open(errStream, err);
    
    d_log << level(LOGCOMMANDS) << gpgCmd << '\n';

    Process process("/usr/bin/gpg "
                    "--homedir " + d_user.homedir() + ".gnupg " +
                    d_gpgOptions + ' ' + command);

    process.start();

    process << inStream.rdbuf();
    process.close();
    
    thread outThread(collect, &outStream, &process);
    thread errThread(collect, &errStream, &process.cerr());

    outThread.join();
    errThread.join();

    process.waitForChild();
}








