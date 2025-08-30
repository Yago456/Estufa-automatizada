
#include <DHT.h>  

#define DHTPIN 2          
#define DHTTYPE DHT11     
const int pinoLED = 3;   
const int limiteAlerta = 70; 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(pinoLED, OUTPUT);
  
  dht.begin();
  
  Serial.begin(9600);
  
  Serial.println("========================================");
  Serial.println("      PROJETO SENSOR DHT11 REAL");
  Serial.println("========================================");
  Serial.println("Iniciando leitura do sensor...");
  Serial.println("LED acenderá acima de 70% de umidade");
  Serial.println("========================================");
  Serial.println();
  
  digitalWrite(pinoLED, HIGH);
  delay(500);
  digitalWrite(pinoLED, LOW);
  delay(500);
  digitalWrite(pinoLED, HIGH);
  delay(500);
  digitalWrite(pinoLED, LOW);
  
  delay(2000); 
}

void loop() {
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("❌ ERRO: Falha na leitura do DHT11!");
    Serial.println("Verifique as conexões e resistor de 10KΩ");
    delay(2000);
    return;
  }

  if (umidade > limiteAlerta) {
    digitalWrite(pinoLED, HIGH);  
  } else {
    digitalWrite(pinoLED, LOW);   
  }

  Serial.print("🕒 ");
  Serial.print(millis() / 1000);
  Serial.print("s | ");
  
  Serial.print("💧 Umidade: ");
  Serial.print(umidade, 1); 
  Serial.print("%");
  
  Serial.print(" | 🌡️ Temp: ");
  Serial.print(temperatura, 1); 
  Serial.print("°C");
  
  Serial.print(" | 💡 LED: ");
  if (umidade > limiteAlerta) {
    Serial.print("🔴 ACESO");
  } else {
    Serial.print("⚫ APAGADO");
  }
  
  if (umidade > limiteAlerta) {
    Serial.print(" | ⚠️ ALERTA: Umidade alta!");
  } else if (umidade < 30) {
    Serial.print(" | 💨 Umidade muito baixa");
  } else {
    Serial.print(" | ✅ Normal");
  }
  
  Serial.println(); 

  delay(1000); 
}