#include "remailer.ih"

void Remailer::writeMail(string const &boundary)
{
    ofstream out;
    Msg::open(out, d_mailName);

    ifstream in;
    Msg::open(in, d_reencryptedName);

    out << "\n"                         // create the mail te send.
        "--" << boundary << "\n"
        "Content-Type: application/pgp-encrypted\n"
        "Content-Transfer-Encoding: 7bit\n"
        "\n"
        "Version: 1\n"
        "\n"
        "--" << boundary << "\n"
        "Content-Type: application/octet-stream; name=gpg.asc\n"
        "Content-Transfer-Encoding: 7bit\n"
        "\n" <<
        in.rdbuf() << "\n" <<
        "\n" <<
        "--" << boundary << "--\n";

    out.close();
}
