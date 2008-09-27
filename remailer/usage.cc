//                     usage.cc

#include "main.ih"

void usage(std::string  const  &progname)
{
    cout << "\n" <<
    progname << " by " << Icmbuild::author << "\n" <<
    progname << " V" << Icmbuild::version << " " << Icmbuild::year << "\n"
    "\n"
    "Usage: " << progname << " [options] [config]\n"
    "Where:\n"
    "   [options] - optional arguments (short options between parentheses):\n"
    "      --debug (-d)     - debug output shown to cout\n"
    "      --help (-h)      - provide this help\n"
    "      --nr (-n) <nr>   - temporary files will use id number <nr>\n"
    "      --step <name>    - perform a single step:\n"
    "                           org (info from mail),\n"
    "                           dec (decrypt info),\n"
    "                           doc (create doc to send),\n"
    "                           enc (encrypt doc),\n"
    "                           mail (send mail)\n"
    "      --version (-v)   - show version information and terminate\n"
    "   config   - configuration file (~/etc/remailer.rc).\n"
    << endl;
}
