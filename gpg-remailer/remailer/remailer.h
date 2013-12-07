#ifndef _INCLUDED_REMAILER_
#define _INCLUDED_REMAILER_

#include <string>
#include <vector>

#include <bobcat/user>
#include <bobcat/configfile>
#include <bobcat/stat>
#include <bobcat/log>

#include "../enums/enums.h"
#include "../mail/mail.h"
#include "../gpg/gpg.h"

namespace FBB
{
    class Arg;
};

class Remailer: private Enums
{
    enum SigType
    {
        NO_SIGNATURE,           // no signature found
        SIGNATURE_FOUND,        // signature found
        GOOD_SIGNATURE          // good signature found
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

    Mail d_mail;
    GPG  d_gpg;

    SigType d_sigRequired;
    MailType d_mailType = UNKNOWN;

    std::string d_configName;
    std::string d_step;
    std::string d_replyTo;
    std::string d_boundary;
                                            
    std::string d_nr;                   // nr assigned to files
    std::string d_decryptedName;
    std::string d_errName;
    std::string d_mailName;
    std::string d_multipartSignedDataName;
    std::string d_hdrsName;
    std::string d_contentsName;
    std::string d_reencryptName;
    std::string d_reencryptedName;
    std::string d_signatureName;

    std::vector<std::string> d_members;
    std::vector<std::string> d_recipients;

    static void (Remailer::*s_reEncrypt[])(IOContext &);
    
    public:
        Remailer();
        ~Remailer();

        // main() calls these members in sequence:

        void preparations();        // check permissions, set config-args

        void mailContents();        // extracts the Subject.
                                    // With PGP mail:
                                    // convert =20 etc. hex-specs in the
                                    // received mail to chars. 
                                    // Plain mail is merely copied.
                                    // The new file org.x is written.

        void decrypt();             // decrypts the original mail, writes new
                                    // files decrypted.x and signature.x

        void reencrypt();           // writes reencrypted.x and maybe 
                                    //        multipartsigned.x

        void mail();                // mails the re-encrypted file to the
                                    // recipient(s). Correctly specifying the
                                    // Reply-To header is the responsibility 
                                    // of the user.

        FBB::Log &log();            // log stream to use

    private:
        void multiField(std::vector<std::string> &dest, char const *keyWord,
                                                                    int opt);

        void setLog();
        std::string configField(std::string const &field);

        void setFilenames();

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

inline FBB::Log &Remailer::log()
{
    return d_log;
}

#endif
