#pragma once

#include "PN532_SPI.h"
#include "NfcAdapter.h"

namespace NfcShield {

  typedef void (*GuidCallback)(std::string);

  class NfcIdentificationDevice {
    private:
      SPI spiBus;
      PN532_SPI nfcShield;
      NfcAdapter nfcAdapter;
      GuidCallback callback;    // Can't this be replaced my mbed-os Callback ?

    public:
      NfcIdentificationDevice(PinName mosi=p5, PinName miso=p6, PinName sck=p7, PinName cs=p17);

    public:
      void register_callback(GuidCallback function);
      void check_for_tag(void);
  };

};
