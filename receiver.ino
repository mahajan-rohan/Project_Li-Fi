#include<math.h>
#define LED_PIN 13
#define LDR_PIN A0
#define THRESHOLD 500
#define PERIOD 10

bool previousState;
bool currentState;


void setup() 
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Hello from Receiver!" );
  digitalWrite(LED_PIN, LOW);
}

String message = "";
int count=0;

void loop() 
{
  currentState = getLdr();
  if(currentState && !previousState)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(PERIOD*1.5);
    while(1){
      char ch = getByte();
      if(ch=='\n'){
          Serial.println();
          delay(200);
          Serial.println("message : "+message);
          message="";
          digitalWrite(LED_PIN, LOW);
          break;
      }
      else if(ch==NULL){
        break;
      }
      else message += ch;
    }
  }
  previousState = currentState;
}

bool getLdr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? false : true;
}

char getByte()
{
  int res=0;
  int pov=128;
  for(int i = 0; i < 8; i++)
  {
   bool volt = analogRead(LDR_PIN)> THRESHOLD ? false : true;
   Serial.print(volt);
   res += volt*pov;
   pov/=2;
   delay(PERIOD);
  }
  char character = res;
  Serial.print(" -> ");
  Serial.print(character);
  Serial.println();
  return res;
}