#include <Arduino.h>

float TempReading = 0;
float TempReadingVoltage = 0;
float TempFinalK = 0;
float TempFinalC = 0;
float TempC = 0;
float SpannungR1 = 0;
float stromI = 0;

float T_25 = 298;
float Bwert = 3977;
float widerstandMess = 0;
float Rwert = 2200;

float widerstandR1 = 2200;

// Delay ersatz
unsigned long previousMillis = 0;
const long interval = 500;

// Durchlaufzählen

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;

        TempReading = analogRead(A0);
        TempReadingVoltage = 0.004882 * TempReading;
        SpannungR1 = 5 - TempReadingVoltage;
        stromI = SpannungR1 / widerstandR1;

        widerstandMess = TempReadingVoltage / stromI;

        TempFinalK = 1.0 / ((1.0 / T_25) + (1.0 / Bwert) * log10(widerstandMess / Rwert));
        TempC = TempFinalK - 273.15;

        TempFinalC = 2.9126 * TempC - 50.256;

        Serial.print("Temp_Unkorrigiert: ");
        Serial.println(TempC);
        Serial.print("Temp_Korrigiert: ");
        Serial.println(TempFinalC);
    }
}