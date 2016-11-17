#include "mbed.h"
#include "rtos.h"
#include "log.h"
#include "nfc_identification_device.h"

Serial pc(USBTX, USBRX);
DigitalOut aliveLed(LED1);

void show_alive_led(void const *args) {
  while (true) {
    aliveLed = !aliveLed;
    Thread::wait(1000);
  }
}

void process_guid(std::string guid) {
  SimplyLog::Log::i("GUID: %s\r\n", guid.c_str());
}

void read_nfc_tag(void const *args) {
  NfcShield::NfcIdentificationDevice nfcIdentifier(p5, p6, p7, p17); // MOSI, MISO, SCK, !CS
  nfcIdentifier.register_callback(&process_guid);

  while (true) {
    nfcIdentifier.check_for_tag();
    Thread::wait(500);
  }
}

int main() {
  SimplyLog::Log::i("Booting NFC PN532 LoraWan node ...\r\n");

  Thread alive_thread(show_alive_led);
  Thread nfc_read_thread(read_nfc_tag);

  while (true) {
    Thread::wait(500);
  }
}
