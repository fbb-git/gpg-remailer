#include "mail.ih"

void Mail::writePGPmail(string const &reencrypted, string const &boundary)
{
    ofstream out;
    IO::unlink(*d_mailNamePtr);
    IO::open(out, *d_mailNamePtr, d_relax);

    ifstream in;
    Exception::open(in, reencrypted);

    out << "\n"                         // create the mail to send.
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
        in.rdbuf() << "\n"
        "\n"
        "--" << boundary << "--\n";
}





