#include "remailer.ih"

void Remailer::multipart(IOContext &io)
{
    io.toReencrypt << io.line << endl;  // line containing 
                                        // Content-Type: multipart

    copyToBoundary(io.toReencrypt, io.decrypted);
    copySignature(io.toReencrypt, d_boundary);
    io.toReencrypt << io.decrypted.rdbuf();
}

// Format of the decrypted PGP part:
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
