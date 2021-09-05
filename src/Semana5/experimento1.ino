// IDENTIFICAÇÃO DOS PINOS

int pinoSensor = A0;
int valorSensor = 0;

int pinoLed1 = 12;
int pinoLed2 = 11;
int pinoLed3 = 10;
int pinoLed4 = 9;


// METODOS

void saida(int valorEntrada) {
  // Configura a saída conforme o valor de entrada do sensor
  if (valorEntrada < 640) {
    digitalWrite(pinoLed1, HIGH);
    
  } else if (valorEntrada < 768) {
    digitalWrite(pinoLed1, HIGH);
    digitalWrite(pinoLed2, HIGH);
    
  } else if (valorEntrada < 896) {
    digitalWrite(pinoLed1, HIGH);
    digitalWrite(pinoLed2, HIGH);
    digitalWrite(pinoLed3, HIGH);
    
  } else if (valorEntrada >= 896) {
    digitalWrite(pinoLed1, HIGH);
    digitalWrite(pinoLed2, HIGH);
    digitalWrite(pinoLed3, HIGH);
    digitalWrite(pinoLed4, HIGH);
  }

  // Desliga todas saídas para que o sensor dê novos valores.
  digitalWrite(pinoLed1, LOW);
  digitalWrite(pinoLed2, LOW);
  digitalWrite(pinoLed3, LOW);
  digitalWrite(pinoLed4, LOW);
}


// EXECUÇÃO

void setup() {
  pinMode(pinoSensor, INPUT);

  pinMode(pinoLed1, OUTPUT);
  pinMode(pinoLed2, OUTPUT);
  pinMode(pinoLed3, OUTPUT);
  pinMode(pinoLed4, OUTPUT);
}

void loop() {
  // Entrada
  valorSensor = analogRead(pinoSensor);

  // Saída
  saida(valorSensor);
}
