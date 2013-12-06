#include "remailer.ih"

void Remailer::writeMail(string const &boundary)
{
    ofstream out;
    open(out, d_mailName, UNLINK);

    ifstream in;
    if (d_mailType == CLEAR)                // copy the clear-text mail as-is
    {
        Exception::open(in, d_orgName);
        out << in.rdbuf();
    }
    else
    {
        Exception::open(in, d_reencryptedName);

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
}





