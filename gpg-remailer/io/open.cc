 #include "io.ih"

ofstream &IO::open(ofstream &out, string const &name, bool relax)
{
    try
    {
        Exception::protection(name, 0600);
    }
    catch (exception const &exc)
    {
        if (not relax)
            throw LogException() << exc.what(); 
    }

    out.open(name, ios::ate);

    if (!out)
        throw LogException() << "Can't open (ios::ate) " << name;

    return out;
}

