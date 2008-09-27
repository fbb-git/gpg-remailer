#ifndef _INCLUDED_REMAILER_
#define _INCLUDED_REMAILER_

#include <string>
#include <vector>

#include <bobcat/user>
#include <bobcat/configfile>
#include <bobcat/arg>
#include <bobcat/pattern>

class Remailer
{
    enum SigType
    {
        NO_SIGNATURE,
        SIGNATURE_FOUND,
        GOOD_SIGNATURE 
    };

    FBB::Arg &d_arg;
    FBB::User d_user;
    FBB::ConfigFile d_config;
    std::string d_configName;
    std::string d_step;
    std::string d_replyTo;

    bool d_keepFiles;

    std::string d_nr;                   // nr assigned to files
    std::string d_orgName;
    std::string d_decryptedName;
    std::string d_signatureName;
    std::string d_reencryptName;
    std::string d_reencryptedName;
    std::string d_errName;
    std::string d_mailName;

    std::vector<std::string> d_members;
    std::vector<std::string> d_recipients;
    std::string d_subject;
    std::string d_gpgOptions;
    SigType d_sigRequired;

    public:
        Remailer();
        ~Remailer();
        void preparations();
        void unhex();
        void decrypt();
        void reencrypt();
        void mail();

    private:
        struct FieldStruct
        {
            std::vector<std::string> &dest;
            FBB::Pattern &pattern;
            std::string &configRegex;
        };
        void multiField(std::vector<std::string> &dest, char const *keyWord);
                                            // add members from config file
        static void addField(std::string const &line, FieldStruct &fs);

        std::string configField(std::string const &field);
        void gpg(std::string const &command);
        void setFilenames();
        bool PGPmessage(std::ostream &out);
        void filter(std::ostream &out);
        void inspect(std::ostream &out, std::string const &line);
        void hexChar(std::ostream &out, std::istream &in);

        void copyTo(std::ostream &out, std::istream &in, 
                                            std::string const &boundary);
        void signatureSection(std::ostream &out, std::string const &boundary);
        struct SigStruct
        {
            std::ostream &out;
            SigType sigType;
        };
        static void signatureFilter(std::string const &line, 
                                    SigStruct &sigStruct);

        void fileToReencrypt();
        void writeReencrypted();
        void setSuffixNr();
        bool step(char const *stepName);

        std::string makeBoundary();
        void writeMail(std::string const &boundary);

        struct MailStruct
        {
            std::string boundary;
            std::string const &mailName;
            std::string const &subject;
            std::string const &replyTo;
        };
        static void sendMail(std::string const &recipient, 
                                MailStruct const &mailStruct); 

        void rmQuotes(std::string &str) const;
};

inline bool Remailer::step(char const *stepName)
{
    return d_step.length() == 0 || d_step == stepName;
}
        
#endif
