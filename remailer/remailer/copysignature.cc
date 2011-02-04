#include "remailer.ih"

void Remailer::copySignature(ostream &out, string const &boundary)
{
    if (boundary.length())
        out <<
            "Content-Type: text/plain; charset=us-ascii\n"
            "Content-Disposition: inline\n"
            "Content-Transfer-Encoding: quoted-printable\n"
            "\n";

    ifstream sig;
    Errno::open(sig, d_signatureName);

    SigStruct sigStruct = {out, NO_SIGNATURE};

    out << '\n';

    for_each(istream_iterator<StringLine>(sig), istream_iterator<StringLine>(),
                                FnWrap::unary(signatureFilter, sigStruct));

    if 
    (
        (d_sigRequired == GOOD_SIGNATURE && 
            sigStruct.sigType != GOOD_SIGNATURE)
        ||
        (d_sigRequired == SIGNATURE_FOUND && 
            sigStruct.sigType == NO_SIGNATURE)
    )
        d_log << level(LOGDEFAULT) << "[Fatal] "
                "Bad or missing signature in " << d_orgName << '\n' << FATAL;

    out << '\n' <<
            boundary << '\n';
}



