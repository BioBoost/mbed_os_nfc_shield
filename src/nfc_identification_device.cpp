#include "nfc_identification_device.h"
#include "globally_unique_identifier.h"
#include "log.h"

namespace NfcShield {

  NfcIdentificationDevice::NfcIdentificationDevice(
    PinName mosi, PinName miso, PinName sck, PinName cs)
      : nfcAdapter(nfcShield), nfcShield(spiBus, cs), spiBus(mosi, miso, sck) {

    SimplyLog::Log::i("Initializing NFC shield\r\n");
    nfcAdapter.begin();
  }

  void NfcIdentificationDevice::register_callback(GuidCallback function) {
    callback = function;
  }

  void NfcIdentificationDevice::check_for_tag(void) {
    if (nfcAdapter.tagPresent()) {
      NfcTag tag = nfcAdapter.read();
      if (tag.hasNdefMessage()) {
        NdefMessage message = tag.getNdefMessage();
        NdefRecord record = message[0];

        NfcShield::GloballyUniqueIdentifier * guid = NfcShield::GloballyUniqueIdentifier::instance_from_record(&record);

        if (callback) {
          (*callback)(guid->get_guid());
        } else {
          SimplyLog::Log::w("No callback attached for NFC shield\r\n");
        }
      }
    }
  }

};
