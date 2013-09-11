 #include "remailer.ih"

ofstream &Remailer::open(ofstream &out, string const &name)
{
    if (Stat stat(name))
    {
        if (stat.mode() != 0600 && not d_relax)
            d_log << "Incorrect mode for existing " << argv[1] << '\n' <<
                     FATAL; 
    }
    else
    {
        int fd = open(argv[1], O_CREAT, S_IRUSR | S_IWUSR);

        if (fd < 0)
            d_log << "Can't create 0600 " << argv[1] << '\n' << FATAL;

        close(fd);
    }

    out.open(name, ios::ate);

    if (!out)
        d_log << "Can't open (ios::ate) " << name << '\n' << FATAL;

    return out;
}

