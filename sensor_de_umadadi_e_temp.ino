// SENSOR DHT11 FÍSICO + LED ALERTA - FUNCIONANDO!
// Com biblioteca DHT para sensor real

#include <DHT.h>  // Biblioteca para o sensor DHT11

// Configurações dos pinos
#define DHTPIN 2          // Pino DATA do DHT11
#define DHTTYPE DHT11     // Tipo do sensor
const int pinoLED = 3;    // Pino do LED de alerta
const int limiteAlerta = 70; // Umidade para LED acender

// Inicializa o sensor DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Configura os pinos
  pinMode(pinoLED, OUTPUT);
  
  // Inicia o sensor DHT
  dht.begin();
  
  // Inicia comunicação serial
  Serial.begin(9600);
  
  // Mensagem inicial bonita
  Serial.println("========================================");
  Serial.println("      PROJETO SENSOR DHT11 REAL");
  Serial.println("========================================");
  Serial.println("Iniciando leitura do sensor...");
  Serial.println("LED acenderá acima de 70% de umidade");
  Serial.println("========================================");
  Serial.println();
  
  // Pisca LED para teste
  digitalWrite(pinoLED, HIGH);
  delay(500);
  digitalWrite(pinoLED, LOW);
  delay(500);
  digitalWrite(pinoLED, HIGH);
  delay(500);
  digitalWrite(pinoLED, LOW);
  
  delay(2000); // Espera o sensor estabilizar
}

void loop() {
  // LÊ OS VALORES REAIS DO DHT11 FÍSICO
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica se a leitura foi bem-sucedida
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("❌ ERRO: Falha na leitura do DHT11!");
    Serial.println("Verifique as conexões e resistor de 10KΩ");
    delay(2000);
    return;
  }

  // CONTROLE DO LED FÍSICO (FUNCIONA DE VERDADE!)
  if (umidade > limiteAlerta) {
    digitalWrite(pinoLED, HIGH);  // ACENDE LED
  } else {
    digitalWrite(pinoLED, LOW);   // APAGA LED
  }

  // MOSTRA NO SERIAL MONITOR
  Serial.print("🕒 ");
  Serial.print(millis() / 1000);
  Serial.print("s | ");
  
  Serial.print("💧 Umidade: ");
  Serial.print(umidade, 1); // 1 casa decimal
  Serial.print("%");
  
  Serial.print(" | 🌡️ Temp: ");
  Serial.print(temperatura, 1); // 1 casa decimal
  Serial.print("°C");
  
  Serial.print(" | 💡 LED: ");
  if (umidade > limiteAlerta) {
    Serial.print("🔴 ACESO");
  } else {
    Serial.print("⚫ APAGADO");
  }
  
  // Mensagens de alerta
  if (umidade > limiteAlerta) {
    Serial.print(" | ⚠️ ALERTA: Umidade alta!");
  } else if (umidade < 30) {
    Serial.print(" | 💨 Umidade muito baixa");
  } else {
    Serial.print(" | ✅ Normal");
  }
  
  Serial.println(); // Nova linha

  delay(1000); // Espera 2 segundos entre leituras
}