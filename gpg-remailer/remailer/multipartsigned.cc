#include "remailer.ih"

    // Third format mentioned in the man-page
void Remailer::multipartSigned(IOContext &io)
{
    findBoundary(io);

    ostream null(0);
    copyToBoundary(null, io.decrypted);           // skip all headers

    copyToBoundary(d_multipartSignedDataName, io.decrypted);

    ostringstream command;
    command << "--verify " << 
            d_decryptedName << " " << d_multipartSignedDataName << 
            " 2> " << d_signatureName;
    gpg(command.str());

    copySignature(io.toReencrypt, d_boundary);

    ifstream data;
    Exception::open(data, d_multipartSignedDataName);

    io.toReencrypt << data.rdbuf();
}


// Format of the decrypted PGP part:
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
