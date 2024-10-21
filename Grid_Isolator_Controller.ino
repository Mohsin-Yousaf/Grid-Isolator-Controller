#include "ACS712.h"

int PLC = 8;

int IsolatorState = 4;
int IsolatorRemote = 3;
int IsolatorButton = 11;         // the number of the input pin
int IsolatorPin = 6;       // the number of the output pin

int WarningPin = 9;

int PLC_State;

int IsolatorPinState = LOW;      // the current state of the output pin
int IsolatorButtonCurrentValue;           // the current reading from the input pin
int IsolatorButtonOldValue = LOW;    // the previous reading from the input pin
int IsolatorRemoteCurrentValue;           // the current reading from the input pin
int IsolatorRemoteOldValue = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long IsolatorToggletime = 0;           // the last time the output pin was toggled
unsigned long debounce = 200;   // the debounce time, increase if the output flickers


void setup()
{
  pinMode(PLC, INPUT);

  pinMode(IsolatorRemote, INPUT);
  pinMode(IsolatorButton, INPUT);

  pinMode(IsolatorState, OUTPUT);
  pinMode(IsolatorPin, OUTPUT);
  
  pinMode(WarningPin, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

////////////////// Isolator Control //////////////////////

  IsolatorRemoteCurrentValue = digitalRead(IsolatorRemote);
  IsolatorButtonCurrentValue = digitalRead(IsolatorButton);
  
  PLC_State = digitalRead(PLC);
  digitalWrite(LED_BUILTIN, PLC_State);

//    if (IsolatorButtonCurrentValue == HIGH && IsolatorButtonOldValue == LOW  && millis() - IsolatorToggletime > debounce && PLC_State == HIGH) || (IsolatorButtonCurrentValue == HIGH && IsolatorButtonOldValue == LOW  && millis() - IsolatorToggletime > debounce && PLC_State == HIGH)
      if ((IsolatorButtonCurrentValue == HIGH && IsolatorButtonOldValue == LOW && 
        millis() - IsolatorToggletime > debounce && PLC_State == HIGH) || 
        (IsolatorRemoteCurrentValue == HIGH && IsolatorRemoteOldValue == LOW && 
        millis() - IsolatorToggletime > debounce && PLC_State == HIGH))
       
  {   if (IsolatorRemoteCurrentValue == HIGH)
         digitalWrite(WarningPin, IsolatorRemoteCurrentValue);
      if (IsolatorButtonCurrentValue == HIGH)   
         digitalWrite(WarningPin, IsolatorButtonCurrentValue);
      
      delay(400);
  }
//    else if (IsolatorButtonCurrentValue == HIGH && IsolatorButtonOldValue == LOW  && millis() - IsolatorToggletime > debounce)
      else if (((IsolatorButtonCurrentValue == HIGH && IsolatorButtonOldValue == LOW) || 
       (IsolatorRemoteCurrentValue == HIGH && IsolatorRemoteOldValue == LOW)) &&
       (millis() - IsolatorToggletime > debounce))
  {
    if (IsolatorPinState == HIGH)
      IsolatorPinState = LOW;
    else
      IsolatorPinState = HIGH;
    IsolatorToggletime = millis();
  }
  digitalWrite(IsolatorPin, IsolatorPinState);
  digitalWrite(IsolatorState, IsolatorPinState);

  
  IsolatorRemoteOldValue = IsolatorRemoteCurrentValue;
  IsolatorButtonOldValue = IsolatorButtonCurrentValue;
  digitalWrite(WarningPin, LOW);
  delay(1);


} 
