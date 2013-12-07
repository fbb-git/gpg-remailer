#include "mail.ih"

void Mail::clearTextMail(string const &org, vector<string> const &recipients)
{
    ifstream in;
    Exception::open(in, org);

    ofstream out;
    Exception::open(out, *d_mailNamePtr);

    out << in.rdbuf();
    out.close();

    for (auto &recipient: recipients)
        sendClearTextMail(recipient);
}
