 #include "remailer.ih"

ofstream &Remailer::open(ofstream &out, string const &name)
{
    Stat stat(name);

    if (stat)
    {
        if (stat.mode() != 0600 && not d_relax)
            d_log << "Incorrect mode for existing " << name << '\n' <<
                     FATAL; 
    }
    else
    {
        int fd = ::open(name.c_str(), O_CREAT, S_IRUSR | S_IWUSR);

        if (fd < 0)
            d_log << "Can't create 0600 " << name << '\n' << FATAL;

        close(fd);
    }

    out.open(name, ios::ate);

    if (!out)
        d_log << "Can't open (ios::ate) " << name << '\n' << FATAL;

    return out;
}

