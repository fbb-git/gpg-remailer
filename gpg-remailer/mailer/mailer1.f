template <class Derived>
Mailer<Derived>::Mailer(FBB::Log &log, Headers &headers, 
               std::string const &mailName, std::string const &step)
:
    MailerBase(log, headers, mailName, step)
{}
