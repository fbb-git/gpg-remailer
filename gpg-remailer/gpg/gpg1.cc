#include "gpg.ih"

GPG::GPG(Log &log, string const &homedir)
:
    d_log(log),
    d_homedir(homedir),

    d_options("--quiet --batch")
{}
