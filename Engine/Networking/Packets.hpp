#ifndef _PACKETS_
#define	_PACKETS_

#include <cstring>
#include "Types.hpp"
#include <stdlib.h>

namespace Packet{

    //Keep packet structure in alphabetic order
    //All packets must be packed.

    #pragma pack(push, 1)
    /**
     * Entity location information from the server.
     */
    struct ServerEntityLocation {
        uint16_t id;
        byte direction;
        float x;
        float y;
    };
    #pragma pack(pop)

};

#endif