// Ultrasonic sensors pins
int trig1 = 22, echo1 = 23, trig2 = 24, echo2 = 25, trig3 = 26, echo3 = 27;
int trig4 = 28, echo4 = 29, trig5 = 30, echo5 = 31, trig6 = 32, echo6 = 33;

float duration1,duration2,duration3,duration4,duration5,duration6;
float distance1, distance2, distance3,distance4, distance5, distance6;
// Threashold distances for all three sensors 
const float set_distance1 = 35, set_distance2 = 35, set_distance3 = 35;

void setup() {
  // put your setup code here, to run once:
    // Set ultrasonic sensor pins
    pinMode(trig1, OUTPUT);
    pinMode(trig2, OUTPUT);
    pinMode(trig3, OUTPUT);
    pinMode(trig4, OUTPUT);
    pinMode(trig5, OUTPUT);
    pinMode(trig6, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(echo2, INPUT);
    pinMode(echo3, INPUT);
    pinMode(echo4, INPUT);
    pinMode(echo5, INPUT);
    pinMode(echo6, INPUT);
    Serial.begin(9600);

}

void loop() {


  Serial.println(distance1);
  dist_measure();

}

void dist_measure() {


    // Send a pulse to the trigger pin
    digitalWrite(trig1, LOW);
    digitalWrite(trig2, LOW);
    digitalWrite(trig3, LOW);
    digitalWrite(trig4, LOW);
    digitalWrite(trig5, LOW);
    digitalWrite(trig6, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    digitalWrite(trig2, HIGH);
    digitalWrite(trig3, HIGH);
    digitalWrite(trig4, HIGH);
    digitalWrite(trig5, HIGH);
    digitalWrite(trig6, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    digitalWrite(trig2, LOW);
    digitalWrite(trig3, LOW);
    digitalWrite(trig4, LOW);
    digitalWrite(trig5, LOW);
    digitalWrite(trig6, LOW);

    // Measure the duration of the pulse on the echo pin
    duration1 = pulseIn(echo1, HIGH,50000);
    duration2 = pulseIn(echo2, HIGH,50000);
    duration3 = pulseIn(echo3, HIGH,50000);
    duration4 = pulseIn(echo4, HIGH,50000);
    duration5 = pulseIn(echo5, HIGH,50000);
    duration6 = pulseIn(echo6, HIGH,50000);
    // Calculate the distance based on the duration of the pulse
    distance1 = (duration1 * 0.034) / 2;
    distance2 = (duration2 * 0.034) / 2;
    distance3 = (duration3 * 0.034) / 2;
    distance4 = (duration4 * 0.034) / 2;
    distance5 = (duration5 * 0.034) / 2;
    distance6 = (duration6 * 0.034) / 2;
}