//#include "mail.ih"
//
//void Mail::pgpMail(string const &reencrypted,
//                   vector<string> const &recipients)
//{
//    string boundary = makePGPBoundary();
//
//    writePGPmail(reencrypted, boundary);    // construct the mail text 
//                                            // from reencrypted.x
//
//    for (auto &recipient: recipients)
//        sendPGPmail(recipient, boundary);
//}
