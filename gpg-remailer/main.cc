#include "main.ih"

using namespace FBB;

namespace   // the anonymous namespace can be used here
{
    Arg::LongOption longOptions[] =
    {
        Arg::LongOption("debug", 'd'),
        Arg::LongOption("help", 'h'),
        Arg::LongOption("logfile", 'l'),
        Arg::LongOption("loglevel", 'L'),
        Arg::LongOption("member", 'm'),
        Arg::LongOption("no-mail"),
        Arg::LongOption("nr", 'n'),
        Arg::LongOption("recipient", 'r'),
        Arg::LongOption("relax"),                   // generates warning
        Arg::LongOption("step", Arg::Required),
        Arg::LongOption("tmp", 't'),
        Arg::LongOption("umask", Arg::Required),
        Arg::LongOption("version", 'v'),
        Arg::LongOption("x-headers", 'x'),
    };

    Arg::LongOption const *const longEnd =
                    longOptions +
                    sizeof(longOptions) / sizeof(Arg::LongOption);
}

int main(int argc, char **argv)
try
{
    Arg::initialize("dhL:l:m:n:r:t:vx", longOptions, longEnd, 
                    argc, argv).versionHelp(usage, version, 0);

    Remailer remailer;

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

        return 0;
    }
}
catch(exception const &err)     // handle exceptions
{
    cerr << "[Fatal] " << err.what() << '\n';
    return 0;
}
catch(int x)
{
    return 0;
}
catch (...)
{
    cerr << "unexpected exception caught in main()\n";
    return 0;
}
