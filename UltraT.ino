#include <PS4Controller.h>  // Biblioteca para controle DualShock
#include "SumoIR.h"  // Biblioteca para os comandos do controle do juiz
#include "DRV8833.h" // para a ponte h 
#include "sensoresIR.h"  // para os sensores frontais
#include "ledFX.h"  // para efeitos de LED

#define boot 0 
// botao 'boot' do ESP32, será utilizado para alternar entre modo auto e RC
int strategy = 0;

//DRV8833 motor(18, 19, 4, 23); // (MotorEsquerdo1, MotorEsquerdo2, MotorDireito1, MotorDireito2)

#include "SeekAndDestroy.h"  
#include "RCDualShock.h"
#include "WildSide.h"


SumoIR IR;

unsigned long tempoPressionado = 0;  // armazena o tempo que o botão foi pressionado
bool botaoPressionado = false;       // indica se o botão foi pressionado


void setup(){
  Serial.begin(115200);

  IR.begin(15);
  PS4.begin("60:5b:b4:7e:74:a4");  // mac do meu ps4 "60:5b:b4:7e:74:a4"  #### mac do pc "9c:30:5b:fb:f4:58"

  motor.begin();
  motor.bip(5, 200, 2000);

  pinMode(boot, INPUT_PULLUP);

  pinMode(leftIRpin, INPUT);
  pinMode(rightIRpin, INPUT);

  pinMode(JsumoLeft, INPUT);
  pinMode(JsumoRight, INPUT);

  pixels.begin();
  pixels.setBrightness(60);
  pixels.clear();
  ledLight(0, 0, 0);
  motor.stop();
}



void loop(){
  // Verifica se o botão foi pressionado
  if (digitalRead(boot) == LOW && !botaoPressionado) {
    tempoPressionado = millis();  // Armazena o tempo atual
    botaoPressionado = true;      // Marca o botão como pressionado
  }

  // Verifica se o botão foi pressionado por mais de 1000ms (1 segundo)
  if (botaoPressionado && (millis() - tempoPressionado >= 1000) && modoAutonomo && !RC) {
    modoAutonomo = false;  // Alterna o modo
    Serial.print("Modo alternado para: ");
    Serial.println(modoAutonomo ? "Autônomo." : "RC.");

    // Reseta a variável do botão pressionado
    botaoPressionado = false;
  }
  if (botaoPressionado && (millis() - tempoPressionado >= 1000) && !modoAutonomo && RC) {
    modoAutonomo = true;  // Alterna o modo
    Serial.print("Modo alternado para: ");
    Serial.println(modoAutonomo ? "Autônomo. " : "RC. ");
    // Reseta a variável do botão pressionado
    botaoPressionado = false;
  }
  
  if (!modoAutonomo) {
    RC = true;
    // Código RC
    DualShock();

  } else if (modoAutonomo) {
    // Código autônomo
    RC = false;
    PS4.setLed(255, 0, 0);   // seta a cor do led do controle
    PS4.sendToController();  // necessário para enviar o comando acima para o controle

    IR.update();

    if (IR.prepare()) {
      motor.stop();
      ledLight(150, 0, 0);
      Serial.println("-> sumo prepare");
    } else if (IR.start()) {
      Serial.println("-> sumo start");
    } else if (IR.on()) {
      pixels.clear();
      ledLight(0, 150, 0);
      Serial.println("-> sumo on");
      
      switch (strategy) {
        default: //fallthrough (vai pro próximo até o break)
        case 4:
          SeekAndDestroy_L();
        break;

        case 5:
          SeekAndDestroy_R();
        break;

        case 6:
          WildSide();
        break;

        case 7:
          motor.move(-1023,-1023);
        break;
        
        case 8:
          teste();
        break;

        // ... outras estratégias
      }

    } else if (IR.stop()) {
      pixels.clear();
      motor.stop();
      Serial.println("-> sumo stop");
      ledDetection();

    } else {
      strategyLED(); // vermelho para estratégia 4, branco para 5 e azul para 6
      
      ledDetection();
    }
  }
}


void strategyLED(){
  int cmd = IR.read();
  if (cmd >= 4 && cmd <= 9) { // faixa de valores validos ( 1, 2 e 3 são reservados pra prepare, start e stop)
    strategy = cmd;
  } else return;

  if (cmd <= 8) {
    const int num_leds = cmd % 8;
    for(uint8_t i = 0; i < num_leds; i++) {
      switch ((cmd-3) % 5) { // Acende o LED de 0 ao número comando numa cor +- diferente cada número
        case 0: pixels.setPixelColor(i, pixels.Color(150, 0,   0  )); break;
        case 1: pixels.setPixelColor(i, pixels.Color(150, 150, 150)); break;
        case 2: pixels.setPixelColor(i, pixels.Color(0,   0,   150)); break;
        case 3: pixels.setPixelColor(i, pixels.Color(255, 150, 0  )); break;
        case 4: pixels.setPixelColor(i, pixels.Color(0,   150, 255)); break;
      } pixels.show();
    }
    delay(80);
    for(uint8_t i = 0; i < num_leds; i++) { 
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Desliga os LEDs
      pixels.show();
    }
    delay(80);
  }
  // if (cmd == 4) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(150, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();      
  //   }
  //   delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }
  // if (cmd == 5) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(150, 150, 150)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //   delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }

  // if (cmd == 6) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 150)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //    delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }

  // if (cmd == 7) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(255, 150, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //    delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }
  // if (cmd == 8) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(150, 150, 150)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //    delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }
}