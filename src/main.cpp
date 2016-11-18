#include "mbed.h"
#include "rtos.h"
#include "log.h"
#include "nfc_identification_device.h"
#include "Simple-LoRaWAN.h"
#include "settings.h"

Serial pc(USBTX, USBRX);
DigitalOut aliveLed(LED1);
SimpleLoRaWAN::Node* node;

void show_alive_led(void const *args) {
  while (true) {
    aliveLed = !aliveLed;
    Thread::wait(1000);
  }
}

void process_guid(std::string guid) {
  SimplyLog::Log::i("GUID: %s\r\n", guid.c_str());
  char buffer[guid.length()+1];
  strcpy(buffer, guid.c_str());
  node->send(buffer, sizeof(buffer)-1);
}

void read_nfc_tag(void const *args) {
  NfcShield::NfcIdentificationDevice nfcIdentifier(p5, p6, p7, p17); // MOSI, MISO, SCK, !CS
  nfcIdentifier.register_callback(&process_guid);

  while (true) {
    nfcIdentifier.check_for_tag();
    Thread::wait(500);
  }
}

void init()
{
  SimplyLog::Log::i("Creating lora node in ABP mode\r\n");
  node = new SimpleLoRaWAN::ABP::Node(devAddr, nwksKey, appKey);
  node->disableLinkCheck();
}

int main() {
  SimplyLog::Log::i("Booting NFC PN532 LoraWan node ...\r\n");
  init();

  Thread alive_thread(show_alive_led);
  Thread nfc_read_thread(read_nfc_tag);

  while (true) {
    node->process();
  }
}
