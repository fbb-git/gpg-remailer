#include "gpg.ih"

void GPG::encrypt(string const &recipients,
                  string const &in, string const &out, string const &err)
{
    run(
        R"(--trust-model always --armor --group members=")" + 
        recipients +
        R"(" -r members --encrypt --sign)",

        in, out, err
    );
}
