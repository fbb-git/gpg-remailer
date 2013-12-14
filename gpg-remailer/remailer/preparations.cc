#include "remailer.ih"

void Remailer::preparations()
{
    if (d_arg.option(0, "relax"))
        d_log << level(LOGDEFAULT) << 
                "--relax ignored. Use `umask 077' instead\n";

    d_keepFiles = d_arg.option(&d_nr, 'n');     // determine predef'd filenr
    if (!d_keepFiles)                           // try fm config file
    {
        d_nr = configField("keepfiles");
        d_keepFiles = d_nr.length() > 0;
    }

    if (d_arg.option('d') || configField("debug") == "true")
    {
        d_keepFiles = true;
        d_log.setLevel(LOGDEBUG);
        d_gpg.debug();
    }

    d_log << level(LOGDEBUG) << 
        "User: " << d_user.name() << " (" << d_user.userid() << ")\n";

    setFilenames();                         // define all used filenames 

    multiField(d_members, "member", 'm');
    multiField(d_recipients, "recipient", 'r');
    multiField(d_envelope, "envelope", 'e');

    checkMembers(d_recipients);

    string signatureRequired = configField("signature");

    ConfigFile::const_iterator iter = d_config.findRE(R"(^\s*replyTo:)");
    if (iter != d_config.end())
    {
        d_replyTo = String::trim(*iter);
        d_replyTo = String::trim(
                        d_replyTo.substr(d_replyTo.find_first_of(" \t")));
        d_replyTo = String::escape(d_replyTo);
    }
    if (d_replyTo.empty())
        throw LogException() << 
                    "Missing `replyTo' specification in config file";

    d_sigRequired = 
        signatureRequired == "good"     ? GOOD_SIGNATURE :
        signatureRequired == "required" ? SIGNATURE_FOUND :
                                          NO_SIGNATURE;
    if (step("hdrs"))
        d_mail.writeHeaders(d_hdrsName);

    string clearText = configField("clear-text");
    if (clearText.empty())
        clearText = "rejected (by default)";

    d_mail.setClearTextMode(
                     clearText == "accepted" || clearText == "envelope" ?
                        ACCEPTED
                    :
                        REJECTED
    );

    if (clearText != "envelope")
    {
        if (d_envelope.size())
        {
            d_log << level(LOGDEFAULT) << 
                "Envelope ignored (clear-text: " << clearText << ")\n";
            d_envelope.clear();
        }            
    }
    else
    {
        checkMembers(d_envelope);

        if (d_log.level() == LOGDEBUG)
        {
            d_log << "Accepted envelope addresses for clear-text e-mail:\n";
            for (auto &address: d_envelope)
                d_log << ' ' << address;
            d_log << '\n';
        }
    }
}


