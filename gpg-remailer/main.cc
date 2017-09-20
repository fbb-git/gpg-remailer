#include "main.ih"

using namespace FBB;

namespace   // the anonymous namespace can be used here
{
    ArgConfig::LongOption longOptions[] =
    {
        ArgConfig::LongOption("debug", 'd'),
        ArgConfig::LongOption("help", 'h'),
        ArgConfig::LongOption("logfile", 'l'),
        ArgConfig::LongOption("loglevel", 'L'),
        ArgConfig::LongOption("member", 'm'),
        ArgConfig::LongOption("no-mail"),
        ArgConfig::LongOption("nr", 'n'),
        ArgConfig::LongOption("recipient", 'r'),
        ArgConfig::LongOption("relax"),                   // generates warning
        ArgConfig::LongOption("step", ArgConfig::Required),
        ArgConfig::LongOption("tmp", 't'),
        ArgConfig::LongOption("umask", ArgConfig::Required),
        ArgConfig::LongOption("version", 'v'),
        ArgConfig::LongOption("x-headers", 'x'),
    };

    ArgConfig::LongOption const *const longEnd =
                    longOptions +
                    sizeof(longOptions) / sizeof(ArgConfig::LongOption);
}

int main(int argc, char **argv)
try
{
    Remailer remailer(usage,
                      "dhL:l:m:n:r:t:vx", longOptions, longEnd, argc, argv);

    try
    {
                                    // using suffix .1 for illlustration
                                    // actual numbers may differ

        remailer.preparations();    // writes hdr.1
        remailer.mailContents();    // writes org.1 + sets mailtype
    
        remailer.decrypt();         // decrypts, writing decrypted.1 and 
                                    // signature.1 (containing info about the
                                    // signature) at step dec or mailtype
                                    // ENCRYPTED. 

        remailer.reencrypt();       // reencrypts at steps doc and enc or 
                                    // when mailtype == ENCRYPTED
                                    // at step doc:
                                    //  writes reencrypt.1, maybe
                                    //  multipartsigned.1 
                                    // at step enc:
                                    //  writes reencrypted.x

        remailer.mail();
    }
    catch (LogException const &err)
    {
        char const *msg = err.msg();
        remailer.log() << "[Fatal] " << msg;

        // ALL exceptions return 0 to prevent unexpected mailer errors in 
        // sendmail's logs.
    }
}
catch(exception const &err)     // handle exceptions
{
    cerr << "[Fatal] " << err.what() << '\n';
}
catch(int)
{}
catch (...)
{
    cerr << "unexpected exception caught in main()\n";
}
