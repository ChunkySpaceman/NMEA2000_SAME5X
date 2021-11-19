#ifndef _NMEA2000_SAME5X_H_
#define _NMEA2000_SAME5X_H_


#include <NMEA2000.h>
#include <N2kMsg.h>


class tNMEA2000_SAME5X : public tNMEA2000
{
protected:
    virtual bool CANSendFrame(unsigned long id, unsigned char len, const unsigned char *buf, bool wait_sent);
    virtual bool CANOpen();
    virtual bool CANGetFrame(unsigned long &id, unsigned char &len, unsigned char *buf);

public:
    tNMEA2000_SAME5X();

};


#endif