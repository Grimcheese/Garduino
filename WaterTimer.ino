const int PUMP_PIN = 13;

const long MAX_PUMP_RUN_TIME = 300000;

bool FIRST_RUN_FLAG = true;

void setup() 
{
  // Initialise pump and ensure it is off
  pinMode(PUMP_PIN, OUTPUT);

  Serial.begin(9600);
 
}

void loop() 
{
  static unsigned long pumpRunTime; // The system time when the pump is turned on
  static unsigned long lastWaterTime; // The system time when the pump is turned off

  unsigned long currentTime = millis();
  if(currentTime % 1000 == 0)
  {
    Serial.print(currentTime);
    Serial.println();
  }

  if(FIRST_RUN_FLAG == true)
  {
    Serial.print("First run");
    Serial.println();
    pumpRunTime = TurnPumpOn();
    Serial.print(pumpRunTime);
    Serial.println();
    
    FIRST_RUN_FLAG = false;
  }

  // If pump is off check time since last water
  if(digitalRead(PUMP_PIN) == HIGH)
  {
    unsigned long timeSinceLastWater = millis() - lastWaterTime;
    if(timeSinceLastWater > 8610000)
    {
      pumpRunTime = TurnPumpOn();
    }
  }
  else
  {
    unsigned long runtime = millis() - pumpRunTime;
    if(runtime > MAX_PUMP_RUN_TIME)
    {
      lastWaterTime = TurnPumpOff(); 
    }
  }
  
}

// Turns off pump and returns system time when pump was turned off
unsigned long TurnPumpOff()
{
  Serial.print("Turning pump off");
  Serial.println();
  
  digitalWrite(PUMP_PIN, HIGH);
  return(millis());
}

// Turns on pump and returns system time when pump was turned on
unsigned long TurnPumpOn()
{
  Serial.print("Turning pump on");
  Serial.println();
  
  digitalWrite(PUMP_PIN, LOW);
  return(millis());
}
