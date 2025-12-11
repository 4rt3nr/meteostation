#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  dht.begin();
  
  lcd.setCursor(0, 0);
  lcd.print("Meteo Station");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(2000);
  
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT error!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error   ");
    return;
  }
  
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 0);
  lcd.print("%");
  
  checkConditions();
}

void checkConditions() {
  if (temperature > 30) {
    lcd.setCursor(12, 0);
    lcd.print("HOT");
  } else if (temperature < 15) {
    lcd.setCursor(12, 0);
    lcd.print("COLD");
  } else {
    lcd.setCursor(12, 0);
    lcd.print("   ");
  }
  
  if (humidity > 70) {
    lcd.setCursor(12, 1);
    lcd.print("HUM");
  } else if (humidity < 30) {
    lcd.setCursor(12, 1);
    lcd.print("DRY");
  } else {
    lcd.setCursor(12, 1);
    lcd.print("   ");
  }
}
