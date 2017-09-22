//                     usage.cc

#include "main.ih"

namespace {

char const usageText[] = R"( [options] [config]
Where:
   [options] - optional arguments (short options between parentheses):
      --debug (-d)     - debug output shown to cout
      --help (-h)      - provide this help
      --logfile (-l) <filename> - log-file name (etc/remailer.log)
      --loglevel (-L) <level> - Set the log-message level: 0: debug
                         1: commands, 2: default
                         `level' implies all higher levels
                         >= 3: no log messages (2)
      --member (-m) <name> - Mail is sent to <name>, members listed
                         in the config file are ignored
      --no-mail        - do not send the reencrypted e-mail
      --nr (-n) <nr>   - temporary files will use id number <nr>
      --recipient (-r) <name> - Mail is sent to <name>, recipients
                         listed in the config file are ignored
      --step <name>    - perform a single step:
                           hdrs (write the mail headers),
                           org (mail data),                    
                           dec (decrypt data),                      
                           doc (create doc to send),                
                           enc (encrypt doc),                       
                           pgpmail (send reencrypted mail)
                           pgpmail:address (reencrypted mail is only sent
                                   to the provided address, ignoring
                                   recipient(s) specified otherwise)
                           clearmail (send clear-text mail)
                           clearmail:address (clear-text mail is only sent
                                   to the provided address, ignoring
                                   recipient(s) specified otherwise)
      --version (-v)   - show version information and terminate
      --x-headers (-x) - in clear-text mode: write `from:', `From:' headers 
                         and headers containing 'envelope' headers to the
                         recipients as X- headers (e.g., X-from:)
   config   - configuration file (~/etc/remailer.rc).
)";

}  // anonymous

void usage(string const &progname)
{
    cout << '\n' <<
    progname << " by f.b.brokken@rug.nl\n" <<
    progname << " V" << version << " " << year << "\n"
        "\n"
        "Usage: " << progname << usageText << endl;
}
