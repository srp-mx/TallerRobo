char estado = ' ';

#define llantas(a, b, c, d) \
  analogWrite(izqF, a); \
  analogWrite(izqA, b); \
  analogWrite(derF, c); \
  analogWrite(derA, d);

int izqF = 11;
int izqA = 10;
int derF = 13;
int derA = 12;

int trigger = 48;
int echo = 49;

int tiempo;
int distancia;

bool automaticoFlag = false;

void automatico()
{
  if (distancia < 30)
  {
    llantas(0, 0, 0, 0);
    delay(500);
    llantas(0, 100, 0, 100);
    delay(300);
    llantas(0, 0, 0, 0);
    delay(500);
    llantas(0, 0, 200, 0);
    delay(250);
    llantas(0, 0, 0, 0);
    delay(200);
  }
  else
  {
    llantas(100, 0, 100, 0);
  }
}

void setup()
{
    Serial.begin(9600);
    Serial2.begin(9600);
    pinMode(izqF, OUTPUT);
    pinMode(izqA, OUTPUT);
    pinMode(derF, OUTPUT);
    pinMode(derA, OUTPUT);
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    digitalWrite(trigger, LOW);
    llantas(0, 0, 0, 0);
}

void loop()
{
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    tiempo = pulseIn(echo, HIGH, 30000);
    distancia = tiempo/58;
    //Serial.println(distancia);
    Serial.println(automaticoFlag);
    if (automaticoFlag)
    {
      automatico();
    }
    if (Serial2.available() > 0)
    {
        estado = Serial2.read();
        Serial.println(estado);

        switch (estado)
        {
          case 'a':
            llantas(100, 0, 100, 0)
            automaticoFlag = false;
            break;
          case 'b':
            llantas(0, 100, 0, 100)
            automaticoFlag = false;
            break;
          case 'c':
            llantas(150, 0, 0, 0)
            automaticoFlag = false;
            break;
          case 'd':
            llantas(0, 0, 100, 0)
            automaticoFlag = false;
            break;
          case 'e':
            llantas(0, 0, 0, 0)
            automaticoFlag = false;
            break;
          case 'f':
            automaticoFlag = true;
            break;
        }
    }
}

