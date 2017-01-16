#ifndef MYBEACON_H
#define MYBEACON_H

#include <tins/tins.h>
using namespace std;
using namespace Tins;

void usage(char *pname);

class myBeacon {
    Dot11Beacon _beacon;
public:
    myBeacon();
    void setHWAddr(HWAddress<6> hw_addr);
    void setSSID(string ssid);
    void setChannel(int ch);
    Dot11Beacon getBeacon() const;
};

#endif // MYBEACON_H
