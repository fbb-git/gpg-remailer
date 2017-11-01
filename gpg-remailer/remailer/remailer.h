#ifndef _INCLUDED_REMAILER_
#define _INCLUDED_REMAILER_

#include <string>
#include <vector>

#include <bobcat/user>
#include <bobcat/log>
#include <bobcat/configfile>

#include "../enums/enums.h"
#include "../mail/mail.h"
#include "../gpg/gpg.h"

#include "../headers/headers.h"

namespace FBB
{
    class Arg;
}

struct Remailer: private Enums
{
    struct Preamble
    {
        FBB::Arg &arg;
        FBB::User user;
        std::string configName;
    };

    private:
        enum SigType
        {
            ABSENT,           // no signature found
            SIGNATURE_REQUIRED,        // signature found
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
    
        struct StepStruct
        {
            std::string stepName;
            MailType    requiredType;
        };


        Preamble const &d_preamble;
    
        bool d_keepFiles;
    
        FBB::ConfigFile d_config;
    
        Headers d_headers;
    
        FBB::Log  d_log;
    
        SigType d_sigRequired;
        MailType d_mailType = UNKNOWN;
    
        std::string d_step;
        std::string d_replyTo;
        std::string d_boundary;
                                                
        std::string d_nr;                   // nr assigned to files
        std::string d_decryptedName;
        std::string d_errName;
        std::string d_mailName;
        std::string d_multipartSignedDataName;
        std::string d_hdrsName;
        std::string d_contentsName;         // original mail contents
        std::string d_reencryptName;
        std::string d_reencryptedName;      // name of the file holding the
                                            // reencrypted contents
        std::string d_signatureName;
    
        std::vector<std::string> d_envelope;    // accepted envelope addresses
                                                // for clear-text mail. 
                                                // empty means: all
        std::vector<std::string> d_members;
        std::vector<std::string> d_recipients;
    
        static void (Remailer::*s_reEncrypt[])(IOContext &);
        static StepStruct s_step[];
        static StepStruct *s_stepEnd;
    
        Mail d_mail;
        GPG  d_gpg;
        
    public:
        Remailer(Preamble const &preamble);

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
                                    // checks signatures at fileToReencrypt ->
                                    // copySignature

        void mail();                // mails the re-encrypted file to the
                                    // recipient(s). Correctly specifying the
                                    // Reply-To header is the responsibility 
                                    // of the user.

        FBB::Log &log();            // log stream to use

    private:
        void multiField(std::vector<std::string> &dest, char const *keyWord,
                                                int opt, bool needElements);

        void setLog();
        std::string configField(std::string const &field);

            // called from 'preparations'
        void setKeepFiles();
        void setDebug();
        void setFilenames();
        void checkRelax();
        void setUmask();
        void setReplyTo();
        void setSigRequired();
        void setClearText();

        void copyToBoundary(std::ostream &out, std::istream &in);

        bool envelopeOK();
        void checkMembers(std::vector<std::string> &target);

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
        bool step(std::string const &stepName);

        bool onlyWS(std::string const &text) const;

        EncryptionEnum encryptionType(IOContext &io);
        void multipart(IOContext &io);
        void multipartSigned(IOContext &io);
        void simple(IOContext &io);

        void findBoundary(IOContext &io);
        bool hasBoundary(std::string const &line, 
                                            std::string const &msgTypeName);

        static unsigned long strToUnsigned(std::string const &str, 
                                    char const *optionName, size_t base = 10);

        static void collect(std::ostream *dest, std::istream *in);
};

inline FBB::Log &Remailer::log()
{
    return d_log;
}

#endif
