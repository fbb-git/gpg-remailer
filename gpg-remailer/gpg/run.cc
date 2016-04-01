#include "gpg.ih"

void GPG::run(string command, string const &in, string const &out,
              string const &err)
{
    command = 
        "/usr/bin/gpg " + d_options + 
        " --homedir " + d_homedir + ".gnupg " + command;

    d_log << level(LOGCOMMANDS) << command << 
            " < " << in <<
            " > " << out <<
            " 2> " << err <<
            '\n';

    Process gpg(Process::CIN | Process::COUT | Process::CERR,
                command);

    ifstream inStream;
    Exception::open(inStream, in);

    gpg.start();
    thread outThread(collector, out.c_str(), gpg.childOutStream().rdbuf());
    thread errThread(collector, err.c_str(), gpg.childErrStream().rdbuf());
    gpg << inStream.rdbuf() << eoi;    

    outThread.join();
    errThread.join();
}








