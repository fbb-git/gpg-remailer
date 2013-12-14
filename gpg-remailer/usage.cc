//                     usage.cc

#include "main.ih"

void usage(string const &progname)
{
    cout << '\n' <<
    progname << " by f.b.brokken@rug.nl\n" <<
    progname << " V" << version << " " << year << "\n"
    "\n"
    "Usage: " << progname << " [options] [config]\n"
    "Where:\n"
    "   [options] - optional arguments (short options between parentheses):\n"
    "      --debug (-d)     - debug output shown to cout\n"
    "      --help (-h)      - provide this help\n"
    "      --logfile (-l) <filename> - log-file name (etc/remailer.log)\n"
    "      --loglevel (-L) <level> - Set the log-message level: 0: debug\n"
    "                         1: commands, 2: default\n"
    "                         `level' implies all higher levels\n"
    "                         >= 3: no log messages (2)\n"
    "      --member (-m) <name> - Mail is sent to <name>, members listed\n"
    "                         in the config file are ignored\n"
    "      --no-mail        - do not send the reencrypted e-mail\n"
    "      --nr (-n) <nr>   - temporary files will use id number <nr>\n"
    "      --recipient (-r) <name> - Mail is sent to <name>, recipients\n"
    "                         listed in the config file are ignored\n"
    "      --step <name>    - perform a single step:\n"
    "                           hdrs (write the mail headers),\n"
    "                           org (mail data),\n"                    
    "                           dec (decrypt data),\n"                      
    "                           doc (create doc to send),\n"                
    "                           enc (encrypt doc),\n"                       
    "                           pgpmail (send reencrypted mail)\n"
    "                           pgpmail:address (reencrypted mail is only "
                                                                    "sent\n"
    "                                   to the provided address, ignoring\n"
    "                                   recipient(s) specified otherwise)\n"
    "                           clearmail (send clear-text mail)\n"
    "                           clearmail:address (clear-text mail is only "
                                                                    "sent\n"
    "                                   to the provided address, ignoring\n"
    "                                   recipient(s) specified otherwise)\n"
    "      --version (-v)   - show version information and terminate\n"
    "   config   - configuration file (~/etc/remailer.rc).\n"
    << endl;
}
