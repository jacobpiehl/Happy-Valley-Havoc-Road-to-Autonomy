#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

// define output pin
#define OUT_PIN 13 // D13 = GPIO13

// any xbox controller
XboxSeriesXControllerESP32_asukiaaa::Core xboxController;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");

  // set mode
  pinMode(OUT_PIN, OUTPUT);
  digitalWrite(OUT_PIN, LOW);
  xboxController.begin();


}

void loop() {
  // put your main code here, to run repeatedly:
  xboxController.onLoop();

  if (xboxController.isConnected()) {
    if (xboxController.isWaitingForFirstNotification()) {
      Serial.println("Connected, waiting for first data...");
    }
    else {
      // Input Stuff
      bool a = xboxController.xboxNotif.btnA;

      if (a) {
        digitalWrite(OUT_PIN, HIGH);
      }
      else {
        digitalWrite(OUT_PIN, LOW);
      }
      //uint16_t lx = xboxController.xboxNotif.joyLHori; // 0-65535, center ~32728
      //uint16_t ly = xboxController.xboxNotif.joyLVert; // hmm interesting
      //uint16_t lt = xboxController.xboxNotif.trigLT; // 0-1023

      //Serial.println(xboxController.xboxNotif.toString());
    }
  }
  else {
    digitalWrite(OUT_PIN, LOW);
    Serial.println("Not connected");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart(); // recover from stuck BLE stack
    }
  }
  delay(20);

  }


