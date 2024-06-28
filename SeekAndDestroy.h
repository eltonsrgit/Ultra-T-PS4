#ifndef SeekAndDestroy_H
#define SeekAndDestroy_H


int EstadoAtual;

void EstadoUpdate(){  // função que atualiza os estados

  EstadoAtual = 1; // sem inimigo
  
  if ( LeftDetection() && RightDetection()){  // enxergando inimigo com os 2 sensores
    EstadoAtual = 2;
  } else if ( LeftDetection() ){ // enxergando com o direito
    EstadoAtual = 3;
  } else if (RightDetection()){ // enxergando com o esquerdo
    EstadoAtual = 4;
  }
   else {
    EstadoAtual = 1; // sem inimigo
  }
}

void SeekAndDestroy_L(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento
  switch (EstadoAtual){
    case 1:
      Serial.println("Searching Enemy...");
      motor.move(-850, 850);
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.move(1023, 1023);
      break;

     case 3:
       Serial.println("Left Detected!");
       motor.move(-800, 800);
       break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(800, -800);
      break;
  }
}


void SeekAndDestroy_R(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento
  switch (EstadoAtual){
    case 1:
      Serial.println("Searching Enemy...");
      motor.stop();
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.move(1023, 1023);
      break;

    case 3:
      Serial.println("Left Detected!");
      motor.move(950, -950);
      break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(-950, 950);
      break;
  }
}

#endif