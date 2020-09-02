// Pin definitions
const int compressor1_ipin = 5;
const int compressor1_spin = 7;

const int compressor2_ipin = 2;
const int compressor2_spin = 8;

const int backing1_ipin = 4;
const int backing1_spin = 6;

const int backing2_ipin = 3;
const int backing2_spin = 9;

const int turbo_ipin = 12;
const int turbo_spin = 10;

const int ig_relay = 11;
const int cg_relay = 13;


class Interlock
{
  int ipin;
  int spin;
  int state;
  bool i_active_high;
  bool s_active_high;

  public:
  Interlock(int _ipin, int _spin, int _state, bool _i_active_high, bool _s_active_high)
  {
    ipin = _ipin;
    spin = _spin;
    pinMode(ipin, OUTPUT);
    pinMode(spin, INPUT);
    state = _state;
    i_active_high = _i_active_high;
    s_active_high = _s_active_high;
  }

  void Trip()
  {
    if (state == LOW)
    {
      digitalWrite(ipin, i_active_high);
    }
    state = HIGH;
  }

  void Release()
  {
    if (state == HIGH)
    {
      digitalWrite(ipin, !i_active_high);
    }
    state = LOW;
  }

  int GetIState()
  {
    return state;
  }

  int GetSState()
  {
    if (s_active_high == true)
    {
      return digitalRead(spin);
    }
    else
    {
      return !digitalRead(spin);
    }
  }
};

class State
{
  int pin;
  bool active_high;
  
  public:
  State(int _pin, bool _active_high)
  {
    pin = _pin;
    pinMode(pin, INPUT);
    active_high = _active_high;
  }

  int GetState()
  {
    if (active_high == true) {
      return digitalRead(pin);
    }
    else {
      return !digitalRead(pin);
    }
  }
};

Interlock backing1_interlock(backing1_ipin, backing1_spin, LOW, true, true);
Interlock backing2_interlock(backing2_ipin, backing2_spin, LOW, true, true);
Interlock compressor1_interlock(compressor1_ipin, compressor1_spin, LOW, true, true);
Interlock compressor2_interlock(compressor2_ipin, compressor2_spin, LOW, true, true);
Interlock turbo_interlock(turbo_ipin, turbo_spin, LOW, true, true);

State ig(ig_relay, true);
State cg(cg_relay, true);

int enable = HIGH;

void setup() {
  Serial.begin(9600);
}

void loop() {
  handleSerial();
  if (enable == HIGH){
    handleInterlock();
  }
}

void handleInterlock()
{
  if ((ig.GetState() == LOW) || (cg.GetState() == LOW)) {
    compressor1_interlock.Trip();
    compressor2_interlock.Trip();
    if (cg.GetState() == LOW){
      turbo_interlock.Trip();
    }
  }
  else {
    compressor1_interlock.Release();
    compressor2_interlock.Release();
    turbo_interlock.Release();
  }
}

void releaseInterlocks(){
  backing1_interlock.Release();
  backing2_interlock.Release();
  compressor1_interlock.Release();
  compressor2_interlock.Release();
  turbo_interlock.Release();
}

void printSerialH(){
  Serial.print("Set HIGH");
  Serial.print("\n");
}

void printSerialL(){
  Serial.print("Set LOW");
  Serial.print("\n");
}

void SerialStatePrint(){
  Serial.print(backing1_interlock.GetSState());
  Serial.print(", ");
  Serial.print(backing2_interlock.GetSState());
  Serial.print(", ");
  Serial.print(compressor1_interlock.GetSState());
  Serial.print(", ");
  Serial.print(compressor2_interlock.GetSState());
  Serial.print(", ");
  Serial.print(turbo_interlock.GetSState());
  Serial.print(", ");
  Serial.print(ig.GetState());
  Serial.print(", ");
  Serial.print(cg.GetState());
  Serial.print("\n");
}

void SerialInterlockPrint(){
  Serial.print(backing1_interlock.GetIState());
  Serial.print(", ");
  Serial.print(backing2_interlock.GetIState());
  Serial.print(", ");
  Serial.print(compressor1_interlock.GetIState());
  Serial.print(", ");
  Serial.print(compressor2_interlock.GetIState());
  Serial.print(", ");
  Serial.print(turbo_interlock.GetIState());
  Serial.print("\n");
}

void SerialInfoPrint() {
  Serial.print("S : print device state (Ok/Fail)\n");
  Serial.print("{backing 1}, {backing 2}, {compressor 1}, {compressor 2}, {turbo}, {ig}, {cg}\n");
  Serial.print("I : print interlock state (Interlocked/Off)\n");
  Serial.print("{backing 1}, {backing 2}, {compressor 1}, {compressor 2}, {turbo}\n");
  Serial.print("E : enable interlock system\n");
  Serial.print("D : disable interlock system\n");
}

void handleSerial() {
  while (Serial.available() > 0) {
    char cmd = Serial.read();
    switch (cmd) {
      case '?':
        SerialInfoPrint();
        break;
      case 'S':
        SerialStatePrint();
        break;
      case 'I':
        SerialInterlockPrint();
        break;
      case 'D':
        enable = LOW;
        Serial.print("disable interlocks\n");
        break;
      case 'E':
        enable = HIGH;
        Serial.print("enable interlocks\n");
        break;
      case 'R':
        Serial.print("reset interlocks\n");
        releaseInterlocks();
        break;
    }  
  }
}
