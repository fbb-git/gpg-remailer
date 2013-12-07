#include "remailer.ih"

// Format of the decrypted PGP part (near line 427 in gpg-remailer(1)):
// ----------------------------------------------------------------------
// Content-Type: multipart/mixed; boundary="f+W+jCU1fRNres8c"
// Content-Disposition: inline
// 
// --f+W+jCU1fRNres8c
// Content-Type: text/plain; charset=us-ascii
// Content-Disposition: inline
// Content-Transfer-Encoding: quoted-printable
// 
// Text of the first attachment
// 
// --f+W+jCU1fRNres8c
// Content-Type: application/pdf
// Content-Disposition: attachment; filename="attachment.pdf"
// Content-Transfer-Encoding: base64
// 
// text of the attachment.pdf in base64 encoding
// 
// --f+W+jCU1fRNres8c--
// ----------------------------------------------------------------------

void Remailer::multipart(IOContext &io)
{
    d_log << level(LOGDEBUG) << "Multipart\n";

    io.toReencrypt << io.line << endl;  // line containing 
                                        // Content-Type: multipart

    copyToBoundary(io.toReencrypt, io.decrypted);

    copySignature(io.toReencrypt, d_boundary);
    io.toReencrypt << io.decrypted.rdbuf();
}

