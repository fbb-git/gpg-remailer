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
        Arg::LongOption("nr", 'n'),
        Arg::LongOption("no-mail", 'n'),
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
    Arg::initialize("dhL:l:n:v", longOptions, longEnd, 
                    argc, argv).versionHelp(usage, version, 0);

    Remailer remailer;

    remailer.preparations();
    remailer.unhex();
    remailer.decrypt();
    remailer.reencrypt();
    remailer.mail();

    return 0;
}
    // ALL exceptions return 0 to prevent unexpected mailer errors in 
    // sendmail's logs.
catch(Errno const &err)     // handle exceptions
{
    if (err.which() != 0)
        cerr << "Remailer: " << err.what() << endl;
    return 0;
}
catch(int x)
{
    return 0;
}
catch (...)
{
    cerr << "Remailer: unexpected exception caught in main()\n";
    return 0;
}


