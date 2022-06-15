#include <iostream>
#include <Poco/ConsoleChannel.h>
#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Common/Exception.h>
#include <Access/KerberosInit.h>

using namespace DB;

int main(int argc, char ** argv)
{
    std::cout << "Kerberos Init" << "\n";

    if (argc < 3)
    {
        std::cout << "kerberos_init obtains and caches an initial ticket-granting ticket for principal." << "\n\n";
        std::cout << "Usage:" << "\n" << "    kerberos_init keytab principal [cache]" << "\n";
        return 0;
    }

    String cache_name = "";
    if (argc == 4)
        cache_name = argv[3];

    Poco::AutoPtr<Poco::ConsoleChannel> app_channel(new Poco::ConsoleChannel(std::cerr));
    Poco::Logger::root().setChannel(app_channel);
    Poco::Logger::root().setLevel("trace");

    try
    {
        kerberosInit(argv[1], argv[2], cache_name);
    } catch (const Exception & e) {
         std::cout << "KerberosInit failure: " << getExceptionMessage(e, false) << "\n";
        return -1;
    }
    std::cout << "Done" << "\n";
    return 0;
}
