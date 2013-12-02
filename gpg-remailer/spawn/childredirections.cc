#include "spawn.ih"

void Spawn::childRedirections()
{
    d_inRedirector.through(Redirector::STDIN);
    d_outRedirector.through(Redirector::STDOUT);
    d_errRedirector.through(Redirector::STDERR);    
}

