/*
  This has been coded by Berk Yozkan to run simple tasks over a basic conveyor belt.
  To find out more about the project check the github page: https://github.com/users/berkyoskan/projects/3
  This code is in the public domain.
*/
#define pot A0 //Defining the pin for potentiometer
#define led 9  // Defining the pin for statis led.
#define dir 5  // Defining the pin of the step motor driver for the direction input
#define pul 2  // Defining the pin o f the step motor driver for pulsing
#define en 8   // Defining the pin of step motor driver for enabling
int potvalue, inverted, timer, ledbrightness;// Defining integer values for the value from potentiometer, to have an inverted value, to set a timer, to adjust led brightness.

void setup() {
  pinMode(en, OUTPUT);  //Defining en as an output
  pinMode(pul, OUTPUT); //Defining pul as an output
  pinMode(dir, OUTPUT); //Defining dir as an output
  pinMode(led, OUTPUT); //Defining led as an output
  pinMode(pot, INPUT);  //Defining pot as an input
  digitalWrite(dir, HIGH); //Setting direction pin HIGH
  digitalWrite(led, HIGH); //Setting led pin HIGH as Status LED
  delay(2000);

}

void loop() {
  timer = millis(); //Starting timer
  potvalue = analogRead(pot); //Reading A0 pin to write over potvalue variable
  inverted = 682 - potvalue;  // inverting the potvalue

  if (inverted < 50)// if the inverted value is smaller than 50, then the belt is not enabled free to move by hand but the led is on
  {
    digitalWrite(led, HIGH);
    digitalWrite(en, LOW);

  }
  if (inverted > 49 && inverted < 100) //if the inverted value is equal or bigger than 50, just enable the conveyor motor and make the led blink.
  {
    digitalWrite(en, HIGH);
    digitalWrite(led, LOW);
    delay(100);
    digitalWrite(led, HIGH);
    delay(100);
  }
  else if (inverted > 99 && inverted < 683) //if the inverted value is bigger than 99 and smaller than 683 activate stepper motor depending on the rotation of the potentiometer and make the led bright depending on that value.
  {
    digitalWrite(en, HIGH);
    ledbrightness = map(inverted, 0, 682, 0, 255);
    analogWrite(led, ledbrightness);
    for (int x = 0; x < 100; x++) {
      digitalWrite(pul, HIGH);
      delayMicroseconds(potvalue * 1.2 + 400);
      digitalWrite(pul, LOW);
      delayMicroseconds(potvalue * 1.2 + 400);
    }
  }
}
