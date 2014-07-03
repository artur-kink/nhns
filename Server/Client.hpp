#ifndef _CLIENT_
#define	_CLIENT_

#include "Utilities/Timer.hpp"
#include "Networking/Networking.hpp"

/**
 * Class storing the information of clients connected to server.
 */
class Client{
public:

    enum ClientStatus{
        cs_Disconnected,
        cs_Connecting,
        cs_Connected
    };

    /** Status of this client. */
    ClientStatus status;

    /** Client's network connection. */
    NetworkHandler network;

    /** Time of last received message. */
    Timer timeoutTimer;

    Client();
};

#endif
