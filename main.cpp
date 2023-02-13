/*
	PROGRAMMER.....: Leonel Costa
    DATE...........: 07/02/23
    Changes........: NONE
    OBS............: Rudimentary Alarm
*/

const int PWR_LED = 2;
const int PWR_BTN = 3;
const int PIR_SENSOR = 4;
const int BUZZER = 5;
const bool DEBUG = true;

const int STANDBY = 0;
const int PWR_ON = 1;
const int ALARM_ON = 2;
const int PIR_DETECT = 3;

int alarmState = STANDBY;

void setup(void)
{
  pinMode(PWR_LED , OUTPUT);
  pinMode(PWR_BTN , INPUT);
  pinMode(BUZZER , OUTPUT);
  pinMode(PIR_SENSOR , INPUT);
  digitalWrite(PWR_LED, LOW);
  Serial.begin(9600);
}

void loop(void)
{
  switch(alarmState){
    case STANDBY:{
      if(DEBUG) Serial.println("Standby Test");
      if(digitalRead(PWR_BTN) == false) alarmState = PWR_ON;
      break;
    }
    case PWR_ON:{
      if(DEBUG) Serial.println("POWER-ON");
      digitalWrite(PWR_LED, HIGH);
      delay(3000);
      alarmState = ALARM_ON;
      break;
    }
    case ALARM_ON:{
      if(DEBUG) Serial.println("ALARM ON");
      int PIRsensor = digitalRead(PIR_SENSOR);
      if(PIRsensor == true) {
        alarmState = PIR_DETECT;
      }
    }
    case PIR_DETECT: {
      if(DEBUG) Serial.println("PIR_DETECT");
      for(int i=700;i<800;i++){
        tone(BUZZER,i);
        delay(15);
      }
      for(int i=800;i>700;i--){
        tone(BUZZER,i);
        delay(15);
      }
      noTone(BUZZER);
      alarmState = ALARM_ON;
      break;
    }
  }
}