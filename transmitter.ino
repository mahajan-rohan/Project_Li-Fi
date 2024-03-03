#define LED_PIN 12
#define PERIOD 10

String input="";
int stringLength;

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println("Hello From Transmitter!");
  digitalWrite(LED_PIN, LOW);
}

void loop() 
{
  input="";
  if(Serial.available()>0){
    input = Serial.readString();
    sendMessage(input);

    Serial.println(input);
    Serial.print("Done");
    Serial.println();
    digitalWrite(LED_PIN, LOW);
  }
}

void sendMessage(String string){
  int stringLength = string.length();
  Serial.println("Initiated");
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
  for(int i = 0; i < stringLength; i ++)
  {
    sendByte(string[i]);
    if( (i%3==0 and i!=0) or i==2)   waitTime(); 
  }
  digitalWrite(LED_PIN, LOW);
}

void waitTime(){
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD*10);
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
  return;
}

void sendByte(char my_byte)
{
  String bits = "";
  for (int i = 7; i >= 0; --i) {
        int state = (my_byte & (1 << i))? 1 : 0;
        digitalWrite(LED_PIN, state);
        Serial.print(state);
        delay(PERIOD);
  }
  Serial.print(" -> ");
  Serial.print(my_byte);
  Serial.println();
        
  return;
}