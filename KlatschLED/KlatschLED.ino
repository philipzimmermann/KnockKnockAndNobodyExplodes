//www.elegoo.com
//2016.06.13

int Led = 13; //define LED port
const int buttonpin = 2; //define switch port
int  val; //define digital variable val
unsigned long lastSoundDetectTime = 0;
boolean ledZustand = false;
int counter = 0;
const int tolerance = 600; //This value is tolerated +- for the time between knocks
const int waitingDelay = 2;

void  setup()
{
  pinMode(Led, OUTPUT); //define LED as a output port
  pinMode(buttonpin, INPUT); //define switch as a output port
  Serial.begin(9600);
}

void  loop()
{
  Serial.println(checkKnockPattern(2000, 3));
  delay(3000);
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

void doubleKnock() {
  val = digitalRead(buttonpin); //read the value of the digital interface 3 assigned to val
  if (val == HIGH) //when the switch sensor have signal, LED blink
  {
    lastSoundDetectTime = millis();
    Serial.println("TON 1 WAHRGENOMMEN!");
    delay(80);
    val = digitalRead(buttonpin);
    if (val == LOW) {
      val = digitalRead(buttonpin);
      Serial.println("Warte auf Ton 2");
      boolean ton2 = false;
      while (((millis() - lastSoundDetectTime) < 800) && (val == LOW)) {
        val = digitalRead(buttonpin);
        if (val == HIGH)
        {
          ledZustand = !ledZustand;
          digitalWrite(Led, ledZustand);
          Serial.println("Ton 2 wahrgenommen");
          ton2 = true;
          delay(30);
        }
      }
      if (!ton2) {
        Serial.println("kein Ton 2 wahrgenommen!");
      }
      ton2 = false;
    }
  }
}

void strike() {
  //TODO
  Serial.println("STRIKEEEEE!!!!!");
}

void blinkGreen() {
  setColor(GREEN, 0);
  setColor(GREEN, 1);
  setColor(GREEN, 2);
  delay(250); // Time until a clap is over
  setColor(OFF, 0);
  setColor(OFF, 1);
  setColor(OFF, 2);
}

