#ifndef INCLUDED_MAILER_
#define INCLUDED_MAILER_


class Mailer
{
    FBB::Log &d_log;
    bool d_dontSend;
    std::string const &d_mailName;

    public:
        Mailer(FBB::Log &log, std::string const &mailName, bool dontSend);

        void send(std::string contents, 
                  std::vector<std::string> const &recipients);

    private:
        void sendMail(std::string const &command, std::string const &label, 
                      std::string const &recipient);

        virtual void writeMailContents(std::string const &destination) 
                                                            const = 0;

        virtual std::string const &mailCommand(std::string const &recipients) 
                                                            const = 0; 

        virtual std::string const &label() const = 0;
};
        
#endif
