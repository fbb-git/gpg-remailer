#include "gpg.ih"

int GPG::verify(string const &detachedSig, string const &signedMessage,
                    string const &signatureOutput)
{
    string command = 
        "/usr/bin/gpg " + d_options + 
        " --homedir " + d_homedir + ".gnupg --verify " + 
        detachedSig + " " + signedMessage;

    d_log << level(LOGCOMMANDS) << command << '\n';

    Process gpg(Process::CERR, command);


    gpg.start();

    thread errThread(collector, signatureOutput.c_str(), 
                                gpg.childErrStream().rdbuf());

    errThread.join();

    return gpg.waitForChild();
}
