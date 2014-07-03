#ifndef _MESSAGE_
#define _MESSAGE_

#include <stdlib.h>
#include <string.h>
#include "Types.hpp"

#pragma pack(push, 1)

#define MIN_PACKET_SIZE 2

/** 
* Network message container.
*/
class Message {
    friend class MessageQueue;
public:

    /**
    * Code identifying the message type.
    * c_ = client->server messages.
    * s_ = server->client messages.
    * b_ = server->client or client->server.
    * m_b_Ping is a basic ping message, leave it in.
    * NUM_MESSAGES specifies the number of message codes. It must remain last in the list.
    */
    enum MessageCode {
        m_b_Ping,
        m_c_ClockSyncReq,
        m_s_ClockSyncResp,
        m_c_ConnectionRequest,
        m_s_ConnectionRefuse,
        m_s_ConnectionTerminate,
        m_s_ConnectionAccept,
        m_c_ConnectionComplete,
        m_NUM_MESSAGES
    };

    /** 
    * Message type
    */
    enum MessageGroup {
        /** 
        * Message is from a brand new connection.
        */
        g_NewConnection,

        /** 
        * Message is from a client that is loading.
        */
        g_Loading,

        /** 
        * Standard message.
        */
        g_Normal,

        /** 
        * Message must be sent immediately.
        */
        g_Critical

    };

protected:

    Message(unsigned short inCode, uint32_t time, size_t size, const void* databuffer);
    Message(unsigned short inCode, MessageGroup inGroup, uint32_t time, size_t size, const void* databuffer);
public:

    /** 
    * The message code
    */
    unsigned short code;

    /** 
    * The message group.
    */
    MessageGroup group;

    /** 
    * Server time when message was sent.
    */
    uint32_t serverTime;

    /** 
    * Generic pointer to the data
    */
    void* buffer;

    Message(const Message& other);
    Message(unsigned short inCode, MessageGroup inGroup, uint32_t time);

    Message& operator=(const Message& rhs);

    static uint16_t bufferSize(unsigned short code);
	static byte messageGroup(unsigned short code);

    virtual ~Message();
};
#pragma pack(pop)

#endif