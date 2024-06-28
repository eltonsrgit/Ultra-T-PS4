#ifndef RideTheLightning_H
#define RideTheLightning_H
#include "sensoresIR.h"

bool EsqAt = false;
bool DirAt = false;
enum Estado { NADA, AVANCAR, GIRAR_ESQUERDA, GIRAR_DIREITA, CORRIGE_ESQUERDA, CORRIGE_DIREITA };
Estado estadoAtual = NADA;

// Função para atualizar o estado
void atualizarEstado() {

    if (LeftDetection() && RightDetection()) {
        
        EsqAt = false;
        DirAt = false;
        estadoAtual = AVANCAR;
    } else if (jsumoLeftDet()) {
        
        EsqAt = true;
        DirAt = false;
        estadoAtual = GIRAR_ESQUERDA;
    } else if (jsumoRightDet()) {
        EsqAt = false;
        DirAt = true;
        estadoAtual = GIRAR_DIREITA;
        
    } else if (LeftDetection() && !RightDetection()) {
        
        EsqAt = false;
        DirAt = false;
        estadoAtual = CORRIGE_ESQUERDA;
    } else if (!LeftDetection() && RightDetection()) {
        
        EsqAt = false;
        DirAt = false;
        estadoAtual = CORRIGE_DIREITA;
    }
}

// Função principal que controla o robô
void Lightning() {
  atualizarEstado();

  switch (estadoAtual) {
    case NADA:
        motor.move(-1023, 1023);
        break;

    case AVANCAR:
        motor.stop();
        break;

    case GIRAR_ESQUERDA:
      motor.move(950, -950);
      break;

    case GIRAR_DIREITA:
      motor.move(-950, 950);
      break;

    case CORRIGE_ESQUERDA:
      motor.move(-1023, 1023);
      break;

    case CORRIGE_DIREITA:
      motor.move(1023, -1023);
      break;
  }
}

#endif