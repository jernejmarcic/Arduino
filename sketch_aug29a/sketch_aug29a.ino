// Here we difine which pins are going to be what variable to make changing them easier
const int out1 = 15; // Here for example out1 is pin 15
const int out2 = 2; // Here out2 is connected to pin 2
const int out3 = 0; // I hope you understand now
const int out4 = 4;
const int out5 = 5;
const int out6 = 18;
const int out7 = 22;
const int out8 = 19;

// Here we define which pins are going to be the in* variable to make changing them easier
const int in1 = 39;
const int in2 = 36;
const int in3 = 14;
const int in4 = 27;
const int in5 = 26;
const int in6 = 25;
const int in7 = 33;
const int in8 = 32;
const int in9 = 35;
const int in10 = 34;

const int presstime = 100; //This variable is for the delay between switching the pin from HIGH to LOW, so basically how long the press is
const int dimtime = 2000; //Since DALI wants to be ✨special✨ the light dims before turning off, this delay is enough for the ligh to go from fully on to fully off

const int repetitions = 5; //Here we will set how many times we want the test to be run
// Here we will prepaere the counters so we will now how many times the test has failed or passed
int passed = 0;
int failed = 0;

int readcycles = 0;

void setup() {
  // Below we tell the ESP that the following pins are going to be an output, we need this so stuff gets actually outputed to make press button
  pinMode(out1,OUTPUT); //Here out1 is made as an output
  pinMode(out2,OUTPUT); //And do on
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
  pinMode(out5,OUTPUT);
  pinMode(out6,OUTPUT);
  pinMode(out7,OUTPUT);
  pinMode(out8,OUTPUT);
// Same as above just for input
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  pinMode(in5, INPUT);
  pinMode(in6, INPUT);
  pinMode(in7, INPUT);
  pinMode(in8, INPUT);
  pinMode(in9, INPUT);
  pinMode(in10, INPUT);
  
  
  
  Serial.begin(115200); //Baud rate is set here, make sure it matches the value in the serial monitor or else you'll get giberish
  Serial.println("Test started"); //This just prints out the string on the start of the serial monitor when the sketch is run to tell the user when its starter

  for (int i = 0; i < repetitions; i++) {
    Serial.println("NEW CYCLE, cycle number: " + String(i + 1));
    
//Turn light off for out1
digitalWrite(out1, HIGH);
delay(presstime);
digitalWrite(out1, LOW);
delay(dimtime);
Serial.print("On value for out1: ");
Serial.println(analogRead(in1));
if (analogRead(in1) >= 4000) {
    passed++;
} else {
    failed++;
}

//Turn light on for out1
digitalWrite(out1, HIGH);
delay(presstime);
digitalWrite(out1, LOW);
delay(dimtime);
Serial.print("Off value for out1: ");
Serial.println(analogRead(in1));
if (analogRead(in1) >= 450) {
    passed++;
} else {
    failed++;
}

//Turn light off for out2
digitalWrite(out2, HIGH);
delay(presstime);
digitalWrite(out2, LOW);
delay(dimtime);
Serial.print("On value for out2: ");
Serial.println(analogRead(in2));
if (analogRead(in2) >= 4000) {
    passed++;
} else {
    failed++;
}

//Turn light on for out2
digitalWrite(out2, HIGH);
delay(presstime);
digitalWrite(out2, LOW);
delay(dimtime);
Serial.print("Off value for out2: ");
Serial.println(analogRead(in2));
if (analogRead(in2) >= 450) {
    passed++;
} else {
    failed++;
}

// And similarly for out3 and out4...

//Turn light off for out3
digitalWrite(out3, HIGH);
delay(presstime);
digitalWrite(out3, LOW);
delay(dimtime);
Serial.print("On value for out3: ");
Serial.println(analogRead(in3));
if (analogRead(in3) >= 4000) {
    passed++;
} else {
    failed++;
}

//Turn light on for out3
digitalWrite(out3, HIGH);
delay(presstime);
digitalWrite(out3, LOW);
delay(dimtime);
Serial.print("Off value for out3: ");
Serial.println(analogRead(in3));
if (analogRead(in3) >= 450) {
    passed++;
} else {
    failed++;
}

//Turn light off for out4
digitalWrite(out4, HIGH);
delay(presstime);
digitalWrite(out4, LOW);
delay(dimtime);
Serial.print("On value for out4: ");
Serial.println(analogRead(in4));
if (analogRead(in4) >= 4000) {
    passed++;
} else {
    failed++;
}

//Turn light on for out4
digitalWrite(out4, HIGH);
delay(presstime);
digitalWrite(out4, LOW);
delay(dimtime);
Serial.print("Off value for out4: ");
Serial.println(analogRead(in4));
if (analogRead(in4) >= 450) {
    passed++;
} else {
    failed++;
}



  }

  // Print the test results
  Serial.print("Passed: ");
  Serial.println(passed);
  Serial.print("Failed: ");
  Serial.println(failed);
} 




void loop() {
  // put your main code here, to run repeatedly:
  
 // delay(presstime);
 // digitalWrite(out1, HIGH);
 // delay(presstime);
 // digitalWrite(out1, LOW);
 // delay(waitforoff);



 

}
