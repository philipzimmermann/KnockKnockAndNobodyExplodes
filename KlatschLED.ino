//www.elegoo.com
//2016.06.13

int Led = 13; //define LED port
int buttonpin = 3; //define switch port
int  val; //define digital variable val
unsigned long lastSoundDetectTime = 0;
boolean ledZustand = false;
int counter = 0;

void  setup()
{
  pinMode(Led, OUTPUT); //define LED as a output port
  pinMode(buttonpin, INPUT); //define switch as a output port
  Serial.begin(9600);
}
void  loop()
{
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
      while (((millis() - lastSoundDetectTime) < 800) && (val==LOW)) {
        val = digitalRead(buttonpin);
        if (val == HIGH)
        {
          ledZustand = !ledZustand;
          digitalWrite(Led, ledZustand);
          Serial.println("Ton 2 wahrgenommen");
          ton2=true;
          delay(30);
        }
      }
      if(!ton2){
        Serial.println("kein Ton 2 wahrgenommen!");
      }
      ton2 = false;
    }
  }
}
