int pinLedVermelho = 11;
int pinLedAmarelo = 10;
int pinLedVerde = 9;

void setup() {
  // Configurações iniciais
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
}

void loop() {
  
  // O led verde fica aceso por 2 segundos
  digitalWrite(pinLedVerde, HIGH);
  delay(2000);
  digitalWrite(pinLedVerde, LOW);

  // O led amarelo fica aceso por 1 segundo
  digitalWrite(pinLedAmarelo, HIGH);
  delay(1000);
  digitalWrite(pinLedAmarelo, LOW);

  // O led vermelho fica aceso por 3 segundos
  digitalWrite(pinLedVermelho, HIGH);
  delay(3000);
  digitalWrite(pinLedVermelho, LOW);

}
