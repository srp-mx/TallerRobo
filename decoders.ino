#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define llantas(a, b, c, d) \
  analogWrite(izqF, a); \
  analogWrite(izqA, b); \
  analogWrite(derF, c); \
  analogWrite(derA, d);

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int decoderIzq = 45;
const int decoderDer = 44;

const int izqF = 11;
const int izqA = 10;
const int derF = 13;
const int derA = 12;

constexpr float radioLlanta = 3.25f;

int contadorIzq = 0;
int contadorDer = 0;

bool estadoDecoderIzq;
bool estadoDecoderDer;

float distRecorridaIzq = 0.0f;
float distRecorridaDer = 0.0f;

constexpr int potObj = 200;
int potIzq = potObj;
int potDer = potObj;

#define MUESTRAS 10
int idxMuestra = 0;
float muestrasDistIzq[MUESTRAS] = {};
float muestrasDistDer[MUESTRAS] = {};

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(decoderIzq, INPUT);
  pinMode(decoderDer, INPUT);
  pinMode(izqF, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(derF, OUTPUT);
  pinMode(derA, OUTPUT);
  Serial.begin(9600);
  estadoDecoderIzq = digitalRead(decoderIzq);
  estadoDecoderDer = digitalRead(decoderDer);
}

void loop()
{
  llantas(potIzq, 0, potDer, 0);

  if (digitalRead(decoderDer) != estadoDecoderDer)
  {
    contadorDer++;
    estadoDecoderDer = !estadoDecoderDer;
  }

  if (digitalRead(decoderIzq) != estadoDecoderIzq)
  {
    contadorIzq++;
    estadoDecoderIzq = !estadoDecoderIzq;
  }

  distRecorridaIzq = 0.31415927 * radioLlanta * contadorIzq;
  distRecorridaDer = 0.31415927 * radioLlanta * contadorDer;

  Serial.print("Encoder derecho: ");
  Serial.println(String(contadorDer));
  Serial.print("Encoder izquierdo: ");
  Serial.println(String(contadorIzq));

  lcd.setCursor(0, 0);
  lcd.print(String(distRecorridaIzq));
  lcd.setCursor(0, 1);
  lcd.print(String(distRecorridaDer));
  //lcd.setCursor(0,0);
  //lcd.print(String(0.5 * (distRecorridaIzq + distRecorridaDer)));

  muestrasDistIzq[idxMuestra] = distRecorridaIzq;
  muestrasDistDer[idxMuestra] = distRecorridaDer;

  idxMuestra++;

  if (idxMuestra == MUESTRAS)
  {
    float velIzq = 0.0f;
    float velDer = 0.0f;
    for (int i = 0; i < MUESTRAS - 1; i++)
    {
      velIzq += muestrasDistIzq[i+1] - muestrasDistIzq[i];
      velDer += muestrasDistDer[i+1] - muestrasDistDer[i];
    }

    if (velIzq < velDer - 0.1)
    {
      potIzq += 10;
    }
    else if(velDer < velIzq - 0.1)
    {
      potIzq -= 10;
    }

    if (potDer < 0) potDer = 0;
    if (potIzq < 0) potIzq = 0;
    if (potDer > 255) potDer = 255;
    if (potIzq > 255) potIzq = 255;

    idxMuestra = 0;
  }
}
