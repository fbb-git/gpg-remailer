#ifndef _INCLUDED_REMAILER_
#define _INCLUDED_REMAILER_

#include <string>
#include <vector>

#include <bobcat/user>
#include <bobcat/configfile>
#include <bobcat/stat>
#include <bobcat/log>

namespace FBB
{
    class Arg;
};

class Remailer
{
    enum LOGLEVELS
    {
        LOGDEBUG,
        LOGCOMMANDS,
        LOGDEFAULT
    };

    enum SigType
    {
        NO_SIGNATURE,
        SIGNATURE_FOUND,
        GOOD_SIGNATURE 
    };

    enum EncryptionEnum
    {
        SIMPLE,
        MULTIPART,
        MULTIPART_SIGNED
    };

    struct IOContext
    {
        std::ifstream decrypted;
        std::ofstream toReencrypt;
        std::string   line;
    };

    FBB::Arg &d_arg;

    bool d_keepFiles;
    bool d_relax;                       // relax permission tests

    FBB::ConfigFile d_config;

    FBB::User d_user;
    FBB::Log  d_log;

    SigType d_sigRequired;

    std::string d_configName;
    std::string d_step;
    std::string d_replyTo;
    std::string d_boundary;
    std::string d_subject;
    std::string d_gpgOptions;
                                            
    std::string d_nr;                   // nr assigned to files
    std::string d_decryptedName;
    std::string d_errName;
    std::string d_mailName;
    std::string d_multipartSignedDataName;
    std::string d_orgName;
    std::string d_reencryptName;
    std::string d_reencryptedName;
    std::string d_signatureName;

    std::vector<std::string> d_members;
    std::vector<std::string> d_recipients;

    static void (Remailer::*s_reEncrypt[])(IOContext &);
    
    public:
        Remailer();
        ~Remailer();
        void preparations();
        void unhex();
        void decrypt();
        void reencrypt();
        void mail();

    private:
        void multiField(std::vector<std::string> &dest, char const *keyWord,
                                                                    int opt);

        void setLog();
        std::string configField(std::string const &field);
        void gpg(std::string const &command, std::string const &in,
                    std::string const &out, std::string const &err);
        void setFilenames();
        bool PGPmessage(std::ostream &out);
        void filter(std::ostream &out);
        void inspect(std::ostream &out, std::string const &line);
        void hexChar(std::ostream &out, std::istream &in);

        void copyToBoundary(std::ostream &out, std::istream &in);

        void copySignature(std::ostream &out, std::string const &boundary);
        struct SigStruct
        {
            std::ostream &out;
            SigType sigType;
        };
        static void signatureFilter(std::string const &line, 
                                    SigStruct &sigStruct);

        void copyToBoundary(std::string const &destName, std::istream &in);

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
            FBB::Log &log;
            bool nomail;
        };
        static void sendMail(std::string const &recipient, 
                                MailStruct const &mailStruct); 

        void rmQuotes(std::string &str) const;

        static std::ofstream &open(std::ofstream &out,
                                     std::string const &name);

        void testPermissions(std::string const &path, size_t permissions = 
                FBB::Stat::UR | FBB::Stat::UW | FBB::Stat::UX);

        bool foundIn(std::string const &text, std::string const &target) 
                                                                        const;
        bool onlyWS(std::string const &text) const;

        EncryptionEnum encryptionType(IOContext &io);
        void multipart(IOContext &io);
        void multipartSigned(IOContext &io);
        void simple(IOContext &io);

        void findBoundary(IOContext &io);
        bool hasBoundary(std::string const &line, 
                                            std::string const &msgTypeName);

        static void collect(std::ostream *dest, std::istream *in);
};

#endif
