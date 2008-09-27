#include "remailer.ih"

void Remailer::gpg(string const &command)
{
    Process process(5, "/usr/bin/gpg ");

    process += command;

    msg() << "/usr/bin/gpg " << command << info;

    process.system();
    process.wait();
}
