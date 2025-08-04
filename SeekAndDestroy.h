#ifndef SeekAndDestroy_H
#define SeekAndDestroy_H
#include "sensoresIR.h"
#include "WildSide.h"
#include "DRV8833.h"

DRV8833 motor(19, 18, 23, 4); // motor esquerdo 1, motor esquerdo 2, motor direito 1,  motor direito 2
int EstadoAtual;


void EstadoUpdate(){  // função que atualiza os estados
  int est_ant = EstadoAtual;
  lerSensores();
  EstadoAtual = 1; // sem inimigo
  if (LeftDetection() && RightDetection()){  // enxergando inimigo com os 2 sensores
    EstadoAtual = 2;
  } else if (LeftDetection()){ // enxergando com o direito
    EstadoAtual = 3;
  } else if (RightDetection()){ // enxergando com o esquerdo
    EstadoAtual = 4;
    
  } 
  else if (leftRay == 1) {
    Serial.println("ESQUERDA LATERAL DETECTADO");
    EstadoAtual = 5;
  }
  else if (rightRay == 1) {
    Serial.println("DIREITA LATERAL DETECTADO");
    EstadoAtual = 6;
  }
  else {
    EstadoAtual = 1; // sem inimigo
  }
  
  if (EstadoAtual != est_ant) {
    motor.stop();
    delay(100);
  }
}

void SeekAndDestroy_L(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento
  switch (EstadoAtual){
    case 1:
      
      Serial.println("Searching Enemy...");
      motor.move(-800, 800);
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      
      motor.move(1023, 1023);
      break;

     case 3:
      
      Serial.println("Left Detected!");
      motor.move(-1023, 1023);
      break;

    case 4:
      
      Serial.println("Right Detected!");
      motor.move(1023, -1023);
      break;
  }
}


void SeekAndDestroy_R(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento

  switch (EstadoAtual){

    case 1:
      Serial.println("Searching Enemy...");
      motor.move(800, -800);
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.move(1023, 1023);
      break;

    case 3:
      Serial.println("Left Detected!");
      motor.move(-1023, 1023);
      break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(1023, -1023);
      break;
  }
}

void teste(){
  EstadoUpdate(); // função atualiza o estado a todo momento

  switch (EstadoAtual){

    case 1:
      Serial.println("Searching Enemy...");
      motor.stop();
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.stop();
      break;

    case 3:
      Serial.println("Left Detected!");
      motor.move(-1023, 1023);
      break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(1023, -1023);
      break;
    case 5:
      motor.move(-1023, 1023);
      break;
    case 6:
      motor.move(1023, -1023);
    break;
  }
}



#endif