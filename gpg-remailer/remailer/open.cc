 #include "remailer.ih"

ofstream &Remailer::open(ofstream &out, string const &name, 
                         ExistingFile action)
{
    if (action == UNLINK && unlink(name.c_str()) != 0 && errno != ENOENT)
        d_log << "Can't rm " << name << '\n' << FATAL;

    try
    {
        Exception::protection(name, 0600);
    }
    catch (exception const &exc)
    {
        if (not d_relax)
            d_log << exc.what() << '\n' << FATAL; 
    }

    out.open(name, ios::ate);

    if (!out)
        d_log << "Can't open (ios::ate) " << name << '\n' << FATAL;

    return out;
}

