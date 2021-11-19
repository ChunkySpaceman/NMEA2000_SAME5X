#include <NMEA2000_SAME5X.h>
#include <CAN.h>

//*****************************************************************************
//  Driver dependencies:
//extern CAN CAN;                                                                // Low level CAN needs to be created for us as 'CAN'

//*****************************************************************************
tNMEA2000_SAME5X::tNMEA2000_SAME5X() : tNMEA2000()
{
}



//*****************************************************************************
bool tNMEA2000_SAME5X::CANOpen()
{
    return CAN.begin(250000);
}



//*****************************************************************************
bool tNMEA2000_SAME5X::CANSendFrame(unsigned long id, unsigned char len, const unsigned char *buf, bool wait_sent)
{ 
/*
    CAN.begin(250000);
    CAN.beginExtendedPacket(0xabcdef);
    CAN.write('h');
    CAN.write('e');
    CAN.write('l');
    CAN.write('l');
    CAN.write('o');
    CAN.endPacket();
    Serial.println("sent hello frame");
*/

    CAN.beginExtendedPacket(id);
    for (unsigned char i=0; i<len && i<8; i++) {
        CAN.write(buf[i]);
    }
    CAN.endPacket();
    
    Serial.println(" - sent frame");
    return 1;
}


//*****************************************************************************
bool tNMEA2000_SAME5X::CANGetFrame(unsigned long &id, unsigned char &len, unsigned char *buf)
{
 
 // try to parse packet
    int packetSize = CAN.parsePacket();
    bool HasFrame=false;
 
    CAN_FRAME incoming;
  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

        if ( CAN.available() ) {           // check if data coming
        id=CAN.packetId();
        len=packetSize;
        for (int i=0; i<len && i<8; i++) buf[i]=CAN.read();
        HasFrame=true;
    }

    Serial.println();
  }

    
    
    
    
    
    return HasFrame;
}
