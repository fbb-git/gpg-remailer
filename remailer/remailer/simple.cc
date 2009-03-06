#include "remailer.ih"

void Remailer::simple(IOContext &io)
{
    d_log << level(LOGDEBUG) << "No boundary, no multipart message\n";
    
    // if no boundary and the first line is a content-type then 
    // insert those lines first
    if (io.line.find("Content-Type:") == 0)
    {
        do
            io.toReencrypt << io.line << endl;
        while (getline(io.decrypted, io.line) && not onlyWS(io.line));
    
        io.toReencrypt << endl;
    }

    copySignature(io.toReencrypt, "");
    
    io.toReencrypt << "\n" <<
                    io.line << '\n' << 
                    io.decrypted.rdbuf();
}

// Simple pgp encrypted file.
// Format:
// ----------------------------------------------------------------------
// Content-Type: text/plain; charset=us-ascii
// Content-Disposition: inline
// Content-Transfer-Encoding: quoted-printable
// 
// decrypted text of the message
// ----------------------------------------------------------------------
