#define trigger A0
#define echo A1
#define Relay 8

float time = 0, distance = 0;
float sanitizerLevel = 100.0; // Initial sanitizer level (assumed to be full)

void setup()
{
  Serial.begin(9600);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(Relay, OUTPUT);

  delay(2);
}

void loop()
{
  measure_distance();

  if (distance < 5 && sanitizerLevel > 0) // Check distance and sanitizer level
  {
    digitalWrite(Relay, HIGH);
    delay(2000); // Apply sanitizer for 2 seconds

    // Calculate the amount of sanitizer used
    float sanitizerUsed = 100.0 - sanitizerLevel;
    Serial.print("Sanitizer used: ");
    Serial.print(sanitizerUsed);
    Serial.println("%");

    // Update the sanitizer level
    sanitizerLevel = 100.0 - (distance * 20); // Adjust the formula based on your specific requirements

    if (sanitizerLevel < 0)
      sanitizerLevel = 0;
  }
  else
  {
    digitalWrite(Relay, LOW);
  }

  delay(5000); // Delay before taking the next measurement
}

void measure_distance()
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  time = pulseIn(echo, HIGH);

  distance = time * 0.034 / 2; // Calculate distance in centimeters based on the speed of sound
}
