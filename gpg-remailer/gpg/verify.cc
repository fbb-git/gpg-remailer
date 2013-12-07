#include "gpg.ih"

void GPG::verify(string const &detachedSig, string const &signedMessage,
                    string const &signatureOutput)
{
    run("--verify " + detachedSig + " " + signedMessage,
        "", "", signedMessage
    );
}
