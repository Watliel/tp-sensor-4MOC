#include <DHT.h>

 //include the library code:
#include <LiquidCrystal.h>

//#define DHT_SENSOR_TYPE DHT_TYPE_11
#define DHTPIN 4
#define DHTTYPE DHT11

#define btn 3

DHT dht(DHTPIN, DHTTYPE);

const unsigned long long interval = 3000;
unsigned long long pmilis = 0;

const int button = 3;
int buttonState;
int firstPressed = 0;
float temperatureInitial;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Initialisation");
  pinMode(button, INPUT_PULLUP);
  buttonState = HIGH;

}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  delay(1000);
  buttonState = digitalRead(button);
  if(buttonState == LOW){
    unsigned long long curmilis = millis();
  
  if (curmilis - pmilis >= interval ) {
    pmilis = curmilis;
    if(firstPressed == 0){
      while(isnan(temperature)){
        temperature = dht.readTemperature();
      }
      firstPressed++;
      temperatureInitial = temperature;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("TempIn. = ");
      lcd.print(temperature);
    
    } else {
        if(temperature == temperatureInitial) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("TempIn. = temp.");
          lcd.setCursor(0,1);
          lcd.print(temperature);
        }
        if(temperature > temperatureInitial) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("temp. > TempIn.");
          lcd.setCursor(0,1);
          lcd.print(temperature);
          lcd.print(" > ");
          lcd.print(temperatureInitial);
        }
        if(temperature < temperatureInitial) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("temp. < TempIn.");
          lcd.setCursor(0,1);
          lcd.print(temperature);
          lcd.print(" < ");
          lcd.print(temperatureInitial);
        }
      }
    }
  }
  
  delay(interval);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("temp = ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("humidity = ");
  lcd.print(humidity);
}
