#include "spawn.ih"

void Spawn::childRedirections()
{
    if (d_in != -2)
        d_inRedirector.through(Redirector::STDIN);
    if (d_out != -2)
        d_outRedirector.through(Redirector::STDOUT);
    if (d_err != -2)
        d_errRedirector.through(Redirector::STDERR);    
}

