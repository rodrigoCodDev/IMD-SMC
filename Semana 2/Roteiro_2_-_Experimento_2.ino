
// ----- VARIÁVEIS -----
// Definindo pinos
int pinLedVermelho = 11;
int pinLedAmarelo = 10;
int pinLedVerde = 9;

int pinBtn = 12;
int pinBuzzer = 8;


// Definindo variaveis genericas
bool btnEstado; // Estado do botão (pressionado/solto)
bool semaforoEstado = true; // Estado do funcionamento do semaforo (ligado/desligado)
bool desativacao = false; // Variavel que irá confirmar a desativação do semaforo no final do próximo ciclo

// ----- METÓDOS -----
void semaforo(){
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


// ----- EXECUÇÃO -----
void setup() {
  // Configurações iniciais

  // Leds
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedAmarelo, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);

  // Buzzer
  pinMode(pinBuzzer, OUTPUT);

  // Botão
  pinMode(pinBtn, INPUT);
}


void loop() {

  if (semaforoEstado == true) {
    // Se o semaforo for ligado
    semaforo();


    // Lendo estado do botao
    btnEstado = digitalRead(pinBtn);

    
    if (desativacao == true) {
      // Desativa/desliga o semaforo caso desativacao for true
      semaforoEstado = false;
    }
    
    
    // Confere se o botão está sendo pressionado e se desativacao é false
    if (btnEstado == HIGH and desativacao == false) {
    
      delay(10);
      btnEstado = digitalRead(pinBtn);

      // Confere se o botão ainda está ativado, após 10ms
      if (btnEstado == HIGH) {

        // Registrando desativação do semaforo no final do próximo ciclo
        desativacao = true;
      }
    }
    
  } else {
    // Se o semaforo for desligado
    tone(pinBuzzer, 440);
    delay(2000);
    noTone(pinBuzzer);

    // Retorna a operação do semaforo
    semaforoEstado = true;
    desativacao = false;
  }
  
}
