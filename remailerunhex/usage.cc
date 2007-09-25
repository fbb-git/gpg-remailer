//                     usage.cc

#include "main.ih"

void usage(std::string  const  &progname)
{
    cout << "\n" <<
    progname << " by " << Icmbuild::author << "\n" <<
    progname << " V" << Icmbuild::version << " " << Icmbuild::year << "\n"
    "\n"
    "Usage: " << progname << " < infile > outfile\n"
    "   converts all 2-byte hexadecimal character sequences (following `=') "
                                                                        "in\n"
    "   PGP ascii-armored encrypted blocks (between "
                                      "-----BEGIN PGP MESSAGE-----\n"
    "   and -----END PGP MESSAGE----- markers) to their character-"
                                                            "equivalents.\n"
    << endl;

    throw 1;
}
