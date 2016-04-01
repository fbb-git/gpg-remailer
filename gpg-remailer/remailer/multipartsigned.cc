#include "remailer.ih"

// Format of the decrypted PGP part, having a detached signature 
// (near line 457 in gpg-remailer(1)): 
// ----------------------------------------------------------------------
// Content-Type: multipart/signed; micalg=pgp-sha1; \ (line continues)
//                                      protocol="application/pgp-signature";
//         boundary="=-TNwuMvq+TfajHhvqBuO7"
// 
// --=-TNwuMvq+TfajHhvqBuO7
// Content-Type: text/plain
// Content-Transfer-Encoding: quoted-printable
// 
// Text of the message
// 
// --=-TNwuMvq+TfajHhvqBuO7
// Content-Type: application/pgp-signature; name=signature.asc
// Content-Description: This is a digitally signed message part
// 
// -----BEGIN PGP SIGNATURE-----
// ... signature text
// -----END PGP SIGNATURE-----
// 
// --=-TNwuMvq+TfajHhvqBuO7--
// ----------------------------------------------------------------------

void Remailer::multipartSigned(IOContext &io)
{
    d_log << level(LOGDEBUG) << "Multipart-Signed e-mail received\n";

    findBoundary(io);

    ostream null(0);

    copyToBoundary(null, io.decrypted);  // Copy to the 1st boundary

                                        // Copy the multipart signed msg text
                                        // to multipartsigned.1
    copyToBoundary(d_multipartSignedDataName, io.decrypted);

        // decrypted.1 contains the PGP SIGNATURE block
        // multipartsigned.1 contains the msg txt 
        // signature.1 contains the output of the signature check
    int err = 
        d_gpg.verify(d_decryptedName, d_multipartSignedDataName, 
                     d_signatureName);

    if (err != 0)
    {
        if (d_sigRequired == GOOD_SIGNATURE)
            throw LogException() << "bad or missing signature in " << 
                                d_contentsName << '\n';
        else
            d_log << level(LOGDEFAULT) << 
                "Multipart-Signed e-mail having BAD signature\n";
    }
            

    copySignature(io.toReencrypt, d_boundary);

    ifstream data;
    LogException::open(data, d_multipartSignedDataName);

    io.toReencrypt << data.rdbuf();
}
