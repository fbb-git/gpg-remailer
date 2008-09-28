#include "remailer.ih"

namespace std
{
    inline istream &operator>>(istream &in, string &line)
    {
        return getline(in, line);
    }
}

void Remailer::signatureSection(ostream &out, string const &boundary)
{
    if (boundary.length())
        out <<
            "Content-Type: text/plain; charset=us-ascii\n"
            "Content-Disposition: inline\n"
            "Content-Transfer-Encoding: quoted-printable\n"
            "\n";

    ifstream sig;
    Msg::open(sig, d_signatureName);

    SigStruct sigStruct = {out, NO_SIGNATURE};

    for_each(istream_iterator<string>(sig), istream_iterator<string>(),
        FnWrap1c<string const &, SigStruct &> (signatureFilter, sigStruct));

    if 
    (
        (d_sigRequired == GOOD_SIGNATURE && 
            sigStruct.sigType != GOOD_SIGNATURE)
        ||
        (d_sigRequired == SIGNATURE_FOUND && 
            sigStruct.sigType == NO_SIGNATURE)
    )
        throw Errno(1, "Bad or missing signature in ") << insertable <<
                    d_orgName << throwable;

    out << "\n" <<
            boundary << "\n";
}



