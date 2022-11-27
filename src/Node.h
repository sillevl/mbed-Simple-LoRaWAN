#pragma once

#include "stdint.h"
#include "events/EventQueue.h"
#include "lorawan/LoRaWANInterface.h"
#include "lorawan/LoRaRadio.h"
#include "SX1276_LoRaRadio.h"
#include "rtos.h"
#include "simple-lorawan-config.h"

/**
 * Maximum number of retries for CONFIRMED messages before giving up
 */
#define CONFIRMED_MSG_RETRY_COUNTER     3

namespace SimpleLoRaWAN
{

class Node
{
public:
    Node(events::EventQueue* queue);
    Node(events::EventQueue* queue, Pinmapping pins);
    virtual ~Node();

    void connect(bool wait_until_connected = false);
    void connect(LoRaWANKeys keys, bool wait_until_connected = false);
    bool isConnected();

    // void send(char* data, int size, bool acknowledge = false);
    // void send(unsigned char port, char* data, int size, bool acknowledge = false);
    // void send(uint8_t* data, int size, bool acknowledge = false);
    void send(uint8_t* data, int size, unsigned char port = 1, bool acknowledge = false);

  // Register callbacks
  public:
    void on_connected(mbed::Callback<void()> cb);
    void on_disconnected(mbed::Callback<void()> cb);
    void on_transmitted(mbed::Callback<void()> cb);
    void on_transmission_error(mbed::Callback<void()> cb);

    void enableAdaptiveDataRate();

private:

    SX1276_LoRaRadio radio;
    events::EventQueue ev_queue;
    LoRaWANInterface lorawan;
    lorawan_app_callbacks_t callbacks;

    uint8_t tx_buffer[30];
    uint8_t rx_buffer[30];

    bool connected;

    void initialize();
    void connect(lorawan_connect_t &params);

    void lora_event_handler(lorawan_event_t event);

    // Allows for easy event handler registration
    mbed::Callback<void()> onConnected;
    mbed::Callback<void()> onDisconnected;
    mbed::Callback<void()> onTransmitted;
    mbed::Callback<void()> onTransmissionError;

    void send_message();   // TEMP DUMMY !!!
    void receive_message();   // TEMP DUMMY !!!

//     void setReceiveHandler(void (*fnc)(uint8_t port, uint8_t* data, uint8_t length));

//     void setEventHandler(void (*fnc)(ev_t));
//     void setScanTimeoutEventHandler(void (*fnc)());
//     void setBeaconFoundEventHandler(void (*fnc)());
//     void setBeaconMissedEventHandler(void (*fnc)());
//     void setBeaconTrackedEventHandler(void (*fnc)());
//     void setJoiningEventHandler(void (*fnc)());
//     void setJoinedEventHandler(void (*fnc)());
//     void setRfu1EventHandler(void (*fnc)());
//     void setJoinFailedEventHandler(void (*fnc)());
//     void setRejoinFailedEventHandler(void (*fnc)());
//     void setTxCompleteEventHandler(void (*fnc)());
//     void setLostTSyncEventHandler(void (*fnc)());
//     void setResetEventHandler(void (*fnc)());
//     void setRxCompleteEventHandler(void (*fnc)());
//     void setLinkDeadEventHandler(void (*fnc)());
//     void setLinkAliveEventHandler(void (*fnc)());

//     void enableLinkCheck();
//     void disableLinkCheck();
//     void setLinkCheck(int state);

//     void setSpreadFactor(int spreadfactor);

//     int timeUntilNextSend();

// private:
//     void init();
//     void setLinkCheck();

//     void (*eventHandler)(ev_t);
//     void (*scanTimeoutEventHandler)();
//     void (*beaconFoundEventHandler)();
//     void (*beaconMissedEventHandler)();
//     void (*beaconTrackedEventHandler)();
//     void (*joiningEventHandler)();
//     void (*joinedEventHandler)();
//     void (*rfu1EventHandler)();
//     void (*joinFailedEventHandler)();
//     void (*rejoinFailedEventHandler)();
//     void (*txCompleteEventHandler)();
//     void (*lostTsyncEventHandler)();
//     void (*resetEventHandler)();
//     void (*rxCompleteEventHandler)();
//     void (*linkDeadEventHandler)();
//     void (*linkAliveEventHandler)();
//     void (*receiveHandler)(uint8_t, uint8_t*, uint8_t);
};

} /* namespace SimpleLoRaWAN */

