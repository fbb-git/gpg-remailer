#include "gpg.ih"

void GPG::decrypt(string const &in, string const &out, string const &err)
{
    run("--decrypt ", in, out, err);
}
