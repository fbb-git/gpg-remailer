#include "gpgmail.ih"

void GPGMail::writeMailContents(string const &mailData) const
{
    ifstream in;
    Exception::open(in, mailData);

    ofstream out;
    IO::unlink(d_mailName);
    IO::open(out, d_mailName, d_relax);

    out << "\n"                         // create the mail to send.
        "--" << d_boundary << "\n"
        "Content-Type: application/pgp-encrypted\n"
        "Content-Transfer-Encoding: 7bit\n"
        "\n"
        "Version: 1\n"
        "\n"
        "--" << d_boundary << "\n"
        "Content-Type: application/octet-stream; name=gpg.asc\n"
        "Content-Transfer-Encoding: 7bit\n"
        "\n" <<
        in.rdbuf() << "\n"
        "\n"
        "--" << d_boundary << "--\n";
}





