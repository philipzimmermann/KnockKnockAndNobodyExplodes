//ALGemein
int strikeCounter=0;
int button = 30;
boolean gameON =false;
const int msgOut = 20;
const int msgIn = 21;


//RGBLED:
int leds[9];//o-2 first led rgb.
const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;
const int YELLOW = 3;
const int PURPLE = 4;
const int OFF =5;

//Klatsch:
int Led = 13; //define LED port
const int buttonpin = 2; //define switch port
int  val; //define digital variable val
unsigned long lastSoundDetectTime = 0;
boolean ledZustand = false;
int counter = 0;
const int tolerance = 600; //This value is tolerated +- for the time between knocks
const int waitingDelay = 2;


void setup(){
  
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(button, INPUT);
  pinMode(msgOut, OUTPUT);
  pinMode(msgIn, INPUT_PULLUP );
  setupLED();  
  setupKlatsch();
  attachInterrupt(digitalPinToInterrupt(msgIn) ,msgInterupt,RISING);
 
}

void setupLED()
{
  for(int i= 0; i<9;i++){
    leds[i]=11-i;
    pinMode(leds[i], OUTPUT);
  }

}

void  setupKlatsch()
{
  pinMode(Led, OUTPUT); //define LED as a output port
  pinMode(button, INPUT_PULLUP); //define switch as a output port
  Serial.begin(9600);
}

void loop()
{
  
  
  //Serial.println("Start");
 if(gameON){
  if(digitalRead(button)==LOW){//Button on
    Serial.println("game on");
    if(checkKnockPattern(2000,2)){
      digitalWrite(msgOut,HIGH);
      delay(50);
      digitalWrite(msgOut,LOW);
    }
  
  
  
 }
 }
 

}

void msgInterupt(){
  Serial.println("Signal in");
  if(!gameON){
    gameON=true;
  }else{
    explode();
  }
  
  
}

void setColor(int color, int led){ 
  led=led*3;
  switch(color){
    case RED: 
      analogWrite(leds[led], 255); 
      analogWrite(leds[led+1], 0);
      analogWrite(leds[led+2], 0);
      break; 
      
   case BLUE: 
      analogWrite(leds[led], 0); 
      analogWrite(leds[led+1], 0);
      analogWrite(leds[led+2], 255);
      break; 
   case GREEN: 
      analogWrite(leds[led], 0); 
      analogWrite(leds[led+1], 255);
      analogWrite(leds[led+2], 0);
      break;   
  case PURPLE: 
      analogWrite(leds[led], 255); 
      analogWrite(leds[led+1], 0);
      analogWrite(leds[led+2], 255);
      break;
  case OFF: 
      analogWrite(leds[led], 0); 
      analogWrite(leds[led+1], 0);
      analogWrite(leds[led+2], 0);
      break;         
      default: 
      break;
      
  }
}

boolean checkKnockPattern(int time_dist, int knock_number) {
  setColor(OFF, 0);
  setColor(OFF, 1);
  setColor(OFF, 2);
  int knockCounter = 0;
  //wait for first knock
  Serial.println("Vor schleife");
  do {
    delay(waitingDelay);
    val = digitalRead(buttonpin); //read the value of the digital interface 3 assigned to val
  } while (val == LOW);
  Serial.println("Nach schleife");


  while (knockCounter < knock_number) {
    knockCounter++;
    Serial.print("TON ");
    Serial.print(knockCounter);
    Serial.println("WAHRGENOMMEN!");

    if (knockCounter == knock_number) {
      //Erfolgreich
      Serial.println("checkKnockPattern erfolgreich!!!");
      return true;
    }
    lastSoundDetectTime = millis();
    blinkGreen(); //Let clap cling off
    do {
      delay(waitingDelay);
      val = digitalRead(buttonpin); //read the value of the digital interface 3 assigned to val
      if (millis() - lastSoundDetectTime > time_dist + tolerance) {
        strike();
        return false;
      }
    } while (val == LOW);
    long newSoundDetectTime = millis();
    long timeDiff = newSoundDetectTime - lastSoundDetectTime;
    if (timeDiff > time_dist + tolerance) {
      strike();
      return false;
    }
    if (timeDiff < time_dist - tolerance) {
      strike();
      return false;
    }
  }
}

void strike() {
  Serial.println("STRIKEEEEE!!!!!");
  strikeCounter++;
  if(strikeCounter>=3){
    explode();
  }else{
    digitalWrite(11+strikeCounter, HIGH);
  }
  
}

void blinkGreen() {
  Serial.println("BlinkGreen!!!!!");
  setColor(GREEN, 0);
  setColor(GREEN, 1);
  setColor(GREEN, 2);
  delay(250); // Time until a clap is over
  setColor(OFF, 0);
  setColor(OFF, 1);
  setColor(OFF, 2);
}

void explode(){
  gameON=false;
  digitalWrite(msgOut,HIGH);
  delay(50);
  digitalWrite(msgOut,LOW);
  Serial.println("GAME OVER!!!!!");
  //TODO
}

boolean isButton(){
  return (LOW==digitalRead(button));
}



