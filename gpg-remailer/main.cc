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
        Arg::LongOption("nr", 'n'),
        Arg::LongOption("no-mail"),
        Arg::LongOption("recipient", 'r'),
        Arg::LongOption("relax"),
        Arg::LongOption("step", Arg::Required),
        Arg::LongOption("version", 'v'),
    };

    Arg::LongOption const *const longEnd =
                    longOptions +
                    sizeof(longOptions) / sizeof(Arg::LongOption);
}

int main(int argc, char **argv)
try
{
    Arg::initialize("dhL:l:m:n:r:v", longOptions, longEnd, 
                    argc, argv).versionHelp(usage, version, 0);

    Remailer remailer;

    remailer.preparations();
    remailer.unhex();
    remailer.decrypt();
    remailer.reencrypt();
    remailer.mail();
}
    // ALL exceptions return 0 to prevent unexpected mailer errors in 
    // sendmail's logs.
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