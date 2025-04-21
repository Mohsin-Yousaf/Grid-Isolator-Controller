int BreakerState1 = 5;

int IsolatorState1 = 6;
int IsolatorRemote1 = 3;
int IsolatorButton1 = 4;         // the number of the input pin
int IsolatorPin1 = 9;       // the number of the output pin

int BreakerState2 = A0;

int IsolatorState2 = 12;
int IsolatorRemote2 = A2;
int IsolatorButton2 = A1;         // the number of the input pin
int IsolatorPin2 = 10;       // the number of the output pin

int WarningPin = 11;

int BreakerStateValue1;
int BreakerStateValue2;


int IsolatorPinState1 = LOW;      // the current state of the output pin
int IsolatorButtonCurrentValue1;           // the current reading from the input pin
int IsolatorButtonOldValue1 = LOW;    // the previous reading from the input pin
int IsolatorRemoteCurrentValue1;           // the current reading from the input pin
int IsolatorRemoteOldValue1 = LOW;    // the previous reading from the input pin

int IsolatorPinState2 = LOW;      // the current state of the output pin
int IsolatorButtonCurrentValue2;           // the current reading from the input pin
int IsolatorButtonOldValue2 = LOW;    // the previous reading from the input pin
int IsolatorRemoteCurrentValue2;           // the current reading from the input pin
int IsolatorRemoteOldValue2 = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long IsolatorToggletime1 = 0;           // the last time the output pin was toggled
unsigned long IsolatorToggletime2 = 0;           // the last time the output pin was toggled

unsigned long debounce = 200;   // the debounce time, increase if the output flickers


void setup()
{
  pinMode(BreakerState1, INPUT);
  pinMode(BreakerState2, INPUT);


  pinMode(IsolatorRemote1, INPUT);
  pinMode(IsolatorButton1, INPUT);
  pinMode(IsolatorRemote2, INPUT);
  pinMode(IsolatorButton2, INPUT);

  pinMode(IsolatorState1, OUTPUT);
  pinMode(IsolatorPin1, OUTPUT);
  pinMode(IsolatorState2, OUTPUT);
  pinMode(IsolatorPin2, OUTPUT);
  
  pinMode(WarningPin, OUTPUT);

  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // Read current values for both isolators
  IsolatorRemoteCurrentValue1 = digitalRead(IsolatorRemote1);
  IsolatorButtonCurrentValue1 = digitalRead(IsolatorButton1);
  BreakerStateValue1 = digitalRead(BreakerState1);

  IsolatorRemoteCurrentValue2 = digitalRead(IsolatorRemote2);
  IsolatorButtonCurrentValue2 = digitalRead(IsolatorButton2);
  BreakerStateValue2 = digitalRead(BreakerState2);


  // --- Isolator 1 ---
  if ((IsolatorButtonCurrentValue1 == HIGH && IsolatorButtonOldValue1 == LOW && 
        millis() - IsolatorToggletime1 > debounce && BreakerStateValue1 == HIGH) || 
      (IsolatorRemoteCurrentValue1 == HIGH && IsolatorRemoteOldValue1 == LOW && 
        millis() - IsolatorToggletime1 > debounce && BreakerStateValue1 == HIGH))
  {
    if (IsolatorRemoteCurrentValue1 == HIGH)
      digitalWrite(WarningPin, IsolatorRemoteCurrentValue1);
    if (IsolatorButtonCurrentValue1 == HIGH)
      digitalWrite(WarningPin, IsolatorButtonCurrentValue1);
    
    delay(400);
  }
  else if (((IsolatorButtonCurrentValue1 == HIGH && IsolatorButtonOldValue1 == LOW) || 
            (IsolatorRemoteCurrentValue1 == HIGH && IsolatorRemoteOldValue1 == LOW)) &&
           (millis() - IsolatorToggletime1 > debounce))
  {
    IsolatorPinState1 = !IsolatorPinState1;
    IsolatorToggletime1 = millis();
  }

  digitalWrite(IsolatorPin1, IsolatorPinState1);
  digitalWrite(IsolatorState1, IsolatorPinState1);
  IsolatorRemoteOldValue1 = IsolatorRemoteCurrentValue1;
  IsolatorButtonOldValue1 = IsolatorButtonCurrentValue1;
  digitalWrite(WarningPin, LOW);

  // --- Isolator 2 ---
  if ((IsolatorButtonCurrentValue2 == HIGH && IsolatorButtonOldValue2 == LOW && 
        millis() - IsolatorToggletime2 > debounce && BreakerStateValue2 == HIGH) || 
      (IsolatorRemoteCurrentValue2 == HIGH && IsolatorRemoteOldValue2 == LOW && 
        millis() - IsolatorToggletime2 > debounce && BreakerStateValue2 == HIGH))
  {
    if (IsolatorRemoteCurrentValue2 == HIGH)
      digitalWrite(WarningPin, IsolatorRemoteCurrentValue2);
    if (IsolatorButtonCurrentValue2 == HIGH)
      digitalWrite(WarningPin, IsolatorButtonCurrentValue2);
    
    delay(400);
  }
  else if (((IsolatorButtonCurrentValue2 == HIGH && IsolatorButtonOldValue2 == LOW) || 
            (IsolatorRemoteCurrentValue2 == HIGH && IsolatorRemoteOldValue2 == LOW)) &&
           (millis() - IsolatorToggletime2 > debounce))
  {
    IsolatorPinState2 = !IsolatorPinState2;
    IsolatorToggletime2 = millis();
  }

  digitalWrite(IsolatorPin2, IsolatorPinState2);
  digitalWrite(IsolatorState2, IsolatorPinState2);
  IsolatorRemoteOldValue2 = IsolatorRemoteCurrentValue2;
  IsolatorButtonOldValue2 = IsolatorButtonCurrentValue2;
  digitalWrite(WarningPin, LOW);

  delay(1); // Minimal delay to keep loop responsive
}

