/*******************************************************
Bob Anding  Morse Code OSC
Morse Code Iambic key Oscillator & rig Keyer
(c) 2017, Bob Anding
12-20-17
This is a Tiny starting project for Morse Code and Iambic keys.
The sketch checks an Iambic key for Dits or Dahs. Then plays a tone and lights built-in LED . 
Pin 13 can be used to key a rig. Most modern rigs use logic key input. An Arduino has limited voltage and current handling capabilities.
Using an open-collector transistor, relay or an optoisolator are some common interface options. However the rig interface is left to the User. 
Older rigs and tube rigs may use a different key setup. ALWAYS! Check your rig's keying specs.
***********************************************************/

int Dit = 0; //  use as dit input
int Dah = 2; //  use as dah input
int keyPin = 1; // Logic level output (open collector transistor for keying rig) check rig's specs.
int spkPin = 3; // speaker connected between pin A0 and ground.
int sideTone = 650; // Frequency of side tone
int ditLength = 80; // by setting dit length it will in turn set WPM (60 ~ 30 WPM, 80 ~ 20 WPM, 120 ~ 7 WPM)
int speedPin = A2;

void setup() {
pinMode(speedPin, INPUT);
pinMode(Dit,INPUT); // Dit key input pin 0 , ground pin to send Dit
digitalWrite(Dit,HIGH);//pullup res
pinMode(Dah,INPUT); // Dah key input pin 2 , ground to to send Dah
digitalWrite(Dah,HIGH);//pullup res
pinMode(spkPin,OUTPUT); // spkPin output logic level, may use 100 ohms to limit current
pinMode(keyPin,OUTPUT); // key output pin 1, logic level, limited current , use open collector to key rig

}

void loop() // Reads WPM (speed using ditlength)
{
ditLength = analogRead(speedPin * (20./1023.) + .5); // Read analog voltage on pin 4 (A2) and calculates WPM
 if((digitalRead (Dit))==0) playTone(1);
 if((digitalRead (Dah))==0) playTone(3);
}

//////// constructs character, Plays tone and keys radio   //////////////
void playTone(int Length){
    tone(spkPin,sideTone); 
    digitalWrite(keyPin,1); //turn key output
    delay(Length * ditLength); // use (1 or 3) for Dit or Dah length tone
    noTone(spkPin); // turn off tone
    digitalWrite(keyPin,0); //turn off key output
    delay (ditLength);// add char space

}
