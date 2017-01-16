#include "mybeacon.h"

using namespace std;
using namespace Tins;

void usage(char *pname) {
    cout << "Help: " << pname << " -h" << endl;
    cout << "Usage: " << pname << " <count> <ssid_1>... [<cycle>]" << endl;
    cout << "Usage: " << pname << " 3 gilgil_handsome bob mil [100]" << endl;
    cout << "* Default Beacon cycle is 100 ms" << endl;
    exit(0);
}

myBeacon::myBeacon() {
    _beacon.addr1(Dot11::BROADCAST);
    _beacon.supported_rates({ 1.0f, 5.5f, 11.0f });
    _beacon.rsn_information(RSNInformation::wpa2_psk());
}

/* set MAC Address */
void myBeacon::setHWAddr(HWAddress<6> hw_addr) {
    _beacon.addr2(hw_addr);
    _beacon.addr3(_beacon.addr2());
}

/* set SSID  */
void myBeacon::setSSID(string ssid) {
    _beacon.ssid(ssid);
}

/* set Channel */
void myBeacon::setChannel(int ch) {
    _beacon.ds_parameter_set(ch);
}

/* get Beacon */
Dot11Beacon myBeacon::getBeacon() const{
    return _beacon;
}
