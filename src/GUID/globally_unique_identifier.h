#pragma once

#include "NdefRecord.h"
#include <string.h>

namespace NfcShield {

  class GloballyUniqueIdentifier {
    private:
      static const unsigned int GUID_SIZE = 6;

    private:
      std::string guid;

    public:
      static GloballyUniqueIdentifier * instance_from_record(NdefRecord * record);
      static std::string decode_guid(NdefRecord * record);

    public:
      GloballyUniqueIdentifier(std::string guid);

    public:
      std::string get_guid(void);
  };

};
