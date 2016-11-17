#include "globally_unique_identifier.h"
#include "log.h"

namespace NfcShield {

  GloballyUniqueIdentifier * GloballyUniqueIdentifier::instance_from_record(NdefRecord * record) {
    if (record->getPayloadLength()-1 == GUID_SIZE) {
      return new GloballyUniqueIdentifier(decode_guid(record));
    } else {
      SimplyLog::Log::w("Invalid GUID\r\n");
      return new GloballyUniqueIdentifier("");
    }
  }

  std::string GloballyUniqueIdentifier::decode_guid(NdefRecord * record) {
    char payload[GUID_SIZE+2];
      // +1 for first 0x02 character (ASCII start of text)
      // +1 for \0 we add

    int size = record->getPayloadLength();

    record->getPayload((uint8_t *)payload);
    payload[size] = '\0';
    std::string guid(payload+1);

    return guid;
  }

  GloballyUniqueIdentifier::GloballyUniqueIdentifier(std::string guid) {
    this->guid = guid;
  }

  std::string GloballyUniqueIdentifier::get_guid(void) {
    return this->guid;
  }

};
