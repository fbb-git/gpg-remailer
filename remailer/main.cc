#include "main.ih"

using namespace FBB;

namespace   // the anonymous namespace can be used here
{
    Arg::LongOption longOptions[] =
    {
        Arg::LongOption("debug", 'd'),
        Arg::LongOption("head", 'H'),
        Arg::LongOption("help", 'h'),
        Arg::LongOption("nr", 'n'),
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
    Arg::initialize("dhH:n:v", longOptions, longEnd, 
                    argc, argv).versionHelp(usage, version, 0);

    Remailer remailer;

    remailer.preparations();
    remailer.unhex();
    remailer.decrypt();
    remailer.reencrypt();
    remailer.mail();

    return 0;
}
catch(Errno const &err)     // handle exceptions
{
    cerr << err.what() << endl;
    return err.which();
}
catch(int x)
{
    return x;
}
catch (...)
{
    cerr << "Unexpected exception caught in main()\n";
    return 1;
}


