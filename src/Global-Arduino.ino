#include <Servo.h>

// Definição dos pinos
const int PINO_SERVO_ARM = 9;   // Articulação Vertical (Sobe/Desce)
const int PINO_SERVO_CLAW = 10; // Mecanismo de Captura (Abre/Fecha)
const int PINO_LED_STATUS = 13; // LED de Status da Operação

Servo servoArm;  // Servo 1: Braço
Servo servoClaw; // Servo 2: Garra/Acoamento

void setup()
{
 
  servoArm.attach(PINO_SERVO_ARM, 500, 2500);
  servoClaw.attach(PINO_SERVO_CLAW, 500, 2500);
  

  pinMode(PINO_LED_STATUS, OUTPUT);

  Serial.begin(9600);
  

 
  

  digitalWrite(PINO_LED_STATUS, HIGH);
  delay(1000);
  digitalWrite(PINO_LED_STATUS, LOW);
  
  Serial.println("--- SISTEMA DE COLETA EM MICROGRAVIDADE PRONTO ---");
  Serial.println("Comandos: U (Subir), D (Descer), O (Abrir), C (Fechar)");
}

void loop()
{
  if (Serial.available() > 0) {
    char comando = Serial.read();
    
    // Ignora caracteres de nova linha/retorno de carro comuns no Monitor Serial
    if (comando == '\n' || comando == '\r') return;

    // Pisca o LED rapidamente indicando recepção de comando
    digitalWrite(PINO_LED_STATUS, HIGH);
    delay(100);
    digitalWrite(PINO_LED_STATUS, LOW);
    
    // Processamento dos comandos via teclado
    if (comando == 'U' || comando == 'u') {
      servoArm.write(90); // Ângulo para subir o braço
      Serial.println("[STATUS] Braço: Elevado (Docking)");
    } 
    else if (comando == 'D' || comando == 'd') {
      servoArm.write(45); // Ângulo para descer o braço até a amostra
      Serial.println("[STATUS] Braço: Abaixado (Retrieval)");
    } 
    else if (comando == 'O' || comando == 'o') {
      servoClaw.write(10); // Ângulo de abertura da garra
      Serial.println("[STATUS] Garra: Aberta (Liberada)");
    } 
    else if (comando == 'C' || comando == 'c') {
      servoClaw.write(90); // Ângulo de fechamento para capturar carga
      Serial.println("[STATUS] Garra: Fechada (Carga Segura)");
    }
  }
}
