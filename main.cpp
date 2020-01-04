#include <Arduino.h>

// Enable debug prints to serial monitor
#define MY_DEBUG

// Enable serial gateway
#define MY_GATEWAY_SERIAL

#include <SPI.h>
#include <MySensors.h>
#include <Bounce2.h>

#pragma region class Wlacznik

/**
 * @brief Klasa która porządkuje kod w przypadku użycia wielu wlączników
 * 
 * 
 **/
class Wlacznik
{
private:
public:
  uint8_t ID;         // id obiektu - narastająco o 1 do poprzedniego !!!!!!
  uint8_t RELAY_PIN;  // pin przekaznika
  uint8_t BUTTON_PIN; // pin przycisku
  uint8_t ON;         // stan na wyjsciu przekaznika gdy wlaczony
  uint8_t OFF;        // stan na wyjsciu przekaznika gdy wylaczony
  MyMessage msg;      // obiekt wysylajacy informacje o zdarzeniu do serwera
  Bounce debouncer;
  bool initialValueSent = false;
  Wlacznik(uint8_t id, uint8_t relay_pin, uint8_t button_pin, bool lowLevelTrigger);
  Wlacznik();
  void setup_();
  void present_();
  void loop_();
  void debouncerUpdated();
  void checkMessage(MyMessage message);
};

Wlacznik::Wlacznik(uint8_t id, uint8_t relay_pin, uint8_t button_pin, bool lowLevelTrigger)
{
  ID = id;
  RELAY_PIN = relay_pin;
  BUTTON_PIN = button_pin;
  if (lowLevelTrigger)
  {
    ON = 0;
    OFF = 1;
  }
  else
  {
    ON = 1;
    OFF = 0;
  }

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, loadState(ID) ? ON : OFF); // ustawia poprzedni zapisany stan przekaznika w przypadku zaniku napiecia lub restartu
  debouncer = Bounce();
  msg = MyMessage(ID, V_STATUS);
}
Wlacznik::Wlacznik()
{
}
void Wlacznik::setup_()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(10);
}
void Wlacznik::present_()
{
  present(ID, S_BINARY);
  send(msg.set(0));             // wysyłam do serwera 0 - bez tego controler nie widzi nowych sensorów
  send(msg.set(loadState(ID))); // wysyłam do serwera aktualny stan przekaźnika
}

void Wlacznik::loop_()
{
  if (debouncer.update())
  {
    if (debouncer.read() == LOW)
    {
      saveState(ID, !loadState(ID));
      digitalWrite(RELAY_PIN, loadState(ID) ? ON : OFF);
      send(msg.set(loadState(ID)));
    }
  }
}

void Wlacznik::checkMessage(MyMessage message)
{
  if (message.sensor == ID)
  {
    digitalWrite(RELAY_PIN, message.getBool() ? ON : OFF);
    // Store state in eeprom
    saveState(message.sensor, message.getBool());
    send(msg.set(message.getBool() ? ON : OFF));
  }
}
#pragma endregion

#pragma region class Pir
/*
Klasa która porządkuje kod w przypadku użycia wielu czujek ruchu
*/

class Pir
{
private:
public:
  uint8_t ID;      // id obiektu - narastająco o 1 do poprzedniego !!!!!!
  uint8_t PIR_PIN; // pin Pir
  uint8_t ON;      // stan na wyjsciu przekaznika gdy wlaczony
  uint8_t OFF;     // stan na wyjsciu przekaznika gdy wylaczony
  MyMessage msg;   // obiekt wysylajacy informacje o zdarzeniu do serwera
  Bounce debouncer;
  Pir(uint8_t id, uint8_t pir_pin);
  Pir();
  void setup_();
  void present_();
  void loop_();
  void debouncerUpdated();
};

Pir::Pir(uint8_t id, uint8_t pir_pin)
{
  ID = id;
  PIR_PIN = pir_pin;

  debouncer = Bounce();
  msg = MyMessage(ID, V_TRIPPED);
}
Pir::Pir()
{
}
void Pir::setup_()
{
  pinMode(PIR_PIN, INPUT);
  digitalWrite(PIR_PIN, HIGH);
  debouncer.attach(PIR_PIN);
  debouncer.interval(5);
}
void Pir::present_()
{
  present(ID, S_MOTION);
  send(msg.set(0)); // wysyłam do serwera aktualny stan przekaźnika
}

void Pir::loop_()
{
  if (debouncer.update())
  {
    debouncerUpdated();
  }
}
void Pir::debouncerUpdated()
{
  send(msg.set(debouncer.read() == HIGH ? 1 : 0));
}
#pragma endregion

//--------------------------------------------------------------------------------------------------------------------------------------------
//Tutaj dodajemy urządzenia
//--------------------------------------------------------------------------------------------------------------------------------------------

// Włączniki
Wlacznik w1;
Wlacznik w2;
Wlacznik w3;
Wlacznik w4;
Wlacznik w5;
Wlacznik w6;
Wlacznik w7;
Wlacznik w8;
Wlacznik w9;
Wlacznik w10;
Wlacznik w11;
Wlacznik w12;
Wlacznik w13;
Wlacznik w14;
Wlacznik w15;
Wlacznik w16;
Wlacznik w17;
Wlacznik w18;
Wlacznik w19;
Wlacznik w20;
Wlacznik w21;
Wlacznik w22;
Wlacznik w23;
Wlacznik w24;
Wlacznik w25;

// Pir-y
Pir p1;
Pir p2;
Pir p3;
Pir p4;
Pir p5;
Pir p6;

void before()
{
  w1 = Wlacznik(1, 31, A1, true);
  w2 = Wlacznik(2, 32, A2, true);
  w3 = Wlacznik(3, 33, A3, true);
  w4 = Wlacznik(4, 34, A4, true);
  w5 = Wlacznik(5, 35, A5, true);
  w6 = Wlacznik(6, 36, A6, true);
  w7 = Wlacznik(7, 37, A7, true);
  w8 = Wlacznik(8, 38, A8, true);
  w9 = Wlacznik(9, 39, A9, true);
  w10 = Wlacznik(10, 40, A10, true);
  w11 = Wlacznik(11, 41, A11, true);
  w12 = Wlacznik(12, 42, A12, true);
  w13 = Wlacznik(13, 43, A13, true);
  w14 = Wlacznik(14, 44, A14, true);
  w15 = Wlacznik(15, 45, A15, true);
  w16 = Wlacznik(16, 46, 6, true);
  w17 = Wlacznik(17, 47, 7, true);
  w18 = Wlacznik(18, 48, 8, true);
  w19 = Wlacznik(19, 49, 9, true);
  w20 = Wlacznik(20, 2, 3, true);
  w21 = Wlacznik(21, 4, 5, true);
  w22 = Wlacznik(22, 30, A0, true);
  w23 = Wlacznik(23, 26, 10, true);
  w24 = Wlacznik(24, 27, 11, true);
  w25 = Wlacznik(25, 28, 12, true);

  p1 = Pir(100, 22);
  p2 = Pir(101, 23);
  p3 = Pir(102, 24);
  p4 = Pir(104, 13);
  p5 = Pir(105, 25);
  p6 = Pir(106, 29);
}

void setup()
{
  // Setup locally attached sensors
  delay(1000);
  w1.setup_();
  w2.setup_();
  w3.setup_();
  w4.setup_();
  w5.setup_();
  w6.setup_();
  w7.setup_();
  w8.setup_();
  w9.setup_();
  w10.setup_();
  w11.setup_();
  w12.setup_();
  w13.setup_();
  w14.setup_();
  w15.setup_();
  w16.setup_();
  w17.setup_();
  w18.setup_();
  w19.setup_();
  w20.setup_();
  w21.setup_();
  w22.setup_();
  w23.setup_();
  w24.setup_();
  w25.setup_();

  p1.setup_();
  p2.setup_();
  p3.setup_();
  p4.setup_();
  p5.setup_();
  p6.setup_();
}
void presentation()
{
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("MySensors_Ard1_HA", "1.1");
  w1.present_();
  w2.present_();
  w3.present_();
  w4.present_();
  w5.present_();
  w6.present_();
  w7.present_();
  w8.present_();
  w9.present_();
  w10.present_();
  w11.present_();
  w12.present_();
  w13.present_();
  w14.present_();
  w15.present_();
  w16.present_();
  w17.present_();
  w18.present_();
  w19.present_();
  w20.present_();
  w21.present_();
  w22.present_();
  w23.present_();
  w24.present_();
  w25.present_();

  p1.present_();
  p2.present_();
  p3.present_();
  p4.present_();
  p5.present_();
  p6.present_();
}

void loop()
{
  w1.loop_();
  w2.loop_();
  w3.loop_();
  w4.loop_();
  w5.loop_();
  w6.loop_();
  w7.loop_();
  w8.loop_();
  w9.loop_();
  w10.loop_();
  w11.loop_();
  w12.loop_();
  w13.loop_();
  w14.loop_();
  w15.loop_();
  w16.loop_();
  w17.loop_();
  w18.loop_();
  w19.loop_();
  w20.loop_();
  w21.loop_();
  w22.loop_();
  w23.loop_();
  w24.loop_();
  w25.loop_();

  p1.loop_();
  p2.loop_();
  p3.loop_();
  p4.loop_();
  p5.loop_();
  p6.loop_();
}

void receive(const MyMessage &message)
{
  w1.checkMessage(message);
  w2.checkMessage(message);
  w3.checkMessage(message);
  w4.checkMessage(message);
  w5.checkMessage(message);
  w6.checkMessage(message);
  w7.checkMessage(message);
  w8.checkMessage(message);
  w9.checkMessage(message);
  w10.checkMessage(message);
  w11.checkMessage(message);
  w12.checkMessage(message);
  w13.checkMessage(message);
  w14.checkMessage(message);
  w15.checkMessage(message);
  w16.checkMessage(message);
  w17.checkMessage(message);
  w18.checkMessage(message);
  w19.checkMessage(message);
  w20.checkMessage(message);
  w21.checkMessage(message);
  w22.checkMessage(message);
  w23.checkMessage(message);
  w24.checkMessage(message);
  w25.checkMessage(message);
}
