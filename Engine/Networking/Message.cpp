#include "Message.hpp"

/** 
* Initializes a new instance of the Message class.
* This constructor is used for messages that send no data other than the code.
* @param inCode Message code
* @param inGroup Message group.
*/
Message::Message(unsigned short inCode, MessageGroup inGroup, uint32_t time){

    code = inCode;
    group = inGroup;
    serverTime = time;
    buffer = 0;
}


/** 
* Initializes a new instance of the Message class.
* This constructor is used for messages that send data.
* The data in the databuffer pointer is copied byte wise.
* @param inCode The code.
* @param inGroup The code group.
* @param size Size of data buffer
* @param databuffer Generic pointer to the data buffer
* @see Message
*/
Message::Message(unsigned short inCode, MessageGroup inGroup, uint32_t time, size_t size, const void* databuffer){
    code = inCode;
    group = inGroup;
    serverTime = time;

    if(size > 0){
        buffer = malloc(size);
        memcpy(buffer, databuffer, size);
    }else{
        buffer = 0;
    }
}

/** 
* Initializes a new instance of the Message class.
* This constructor is mainly used for pre parsed messages.
* @param inCode The code.
* @param size Size of data buffer.
* @param databuffer Generic pointer to the data buffer.
*/
Message::Message(unsigned short inCode, uint32_t time, size_t size, const void* databuffer){

    code = inCode;
    group = Message::g_Normal;
    serverTime = time;
    if(size > 0){
        buffer = malloc(size);
        memcpy(buffer, databuffer, size);
    }else{
        buffer = 0;
    }
}

/** 
* Creates a copy of a Message.
* @param other Message to copy.
*/
Message::Message(const Message& other){
    code = other.code;
    group = other.group;
    serverTime = other.serverTime;

}

/** 
* Copy constructor by assignment
* @param rhs Message to make a copy of
*/
Message& Message::operator=(const Message& rhs){
    code = rhs.code;
    group = rhs.group;
    serverTime = rhs.serverTime;

    return *this;
}

/**
* Gets the expected buffer size of a message with the given code.
* @return Size of expected message buffer.
*/
uint16_t Message::bufferSize(unsigned short code){

    switch (code) {
        case Message::m_b_Ping:
            return 0;
        case m_c_ClockSyncReq:
            return 0;
        case m_s_ClockSyncResp:
            return sizeof(uint32_t);
        case m_c_ConnectionRequest:
            return 0;
        case m_s_ConnectionRefuse:
            return 0;
        case m_b_ConnectionTerminate:
            return 0;
        case m_s_ConnectionAccept:
            return 0;
        case m_c_ConnectionComplete:
            return 0;

        case m_c_PlayerMove:
            return sizeof(byte);

        default:
            return 0xFFFF; //Hopefully cause overflow as this should never be reached.
    }
}

/**
* Gets the group of the message with given code.
*/
byte Message::messageGroup(unsigned short code){
	switch (code) {
        case Message::m_b_Ping:
            return Message::g_Critical;
        case m_c_ClockSyncReq:
            return Message::g_Loading;
        case m_s_ClockSyncResp:
            return Message::g_Loading;
        case m_c_ConnectionRequest:
            return Message::g_NewConnection;
        case m_s_ConnectionRefuse:
            return Message::g_NewConnection;
        case m_b_ConnectionTerminate:
            return Message::g_Critical;
        case m_s_ConnectionAccept:
            return Message::g_NewConnection;
        case m_c_ConnectionComplete:
            return Message::g_Loading;

        case m_c_PlayerMove:
            return Message::g_Critical;

        default:
            return 0;
    }
}

/** 
* Clears the data buffer.
*/
Message::~Message(){
    if(buffer != 0){
        free(buffer);
    }
}