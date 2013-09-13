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
    
    Process process(
                    "/usr/bin/gpg --quiet --batch "
                    "--homedir " + d_user.homedir() + ".gnupg " +
                    d_gpgOptions + ' ' + command);

    d_log << level(LOGCOMMANDS) << process.str() << 
            " < " << in <<
            " >> " << out <<
            " 2>> " << err <<
            '\n';

    process.start();

    process << inStream.rdbuf();
    process.close();
    
    thread outThread(collect, &outStream, &process);
    thread errThread(collect, &errStream, &process.cerr());

    outThread.join();
    errThread.join();

    process.waitForChild();
}








