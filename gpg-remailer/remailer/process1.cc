#include "remailer.ih"

void Remailer::process(string const &command, string const &inName)
{
    ifstream in;

    Exception::open(in, inName);

    Process proc(Process:CIN, command);

    while (getline(in, line))
        proc << line << '\n';

    proc.close();
    proc.waitForChild();
}
