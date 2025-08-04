#ifndef sensoresIR_H
#define sensoresIR_H

#define leftIRpin 35
#define rightIRpin 34

#define JsumoLeft 33
#define JsumoRight 32

int leftRay = 0;
int rightRay = 0;

void lerSensores() {
  leftRay = digitalRead(JsumoLeft);
  rightRay = digitalRead(JsumoRight);
}

bool LeftDetection(){
  bool left_IR_read = digitalRead(leftIRpin);
  if (left_IR_read == 0){
    return false; // sem inimigo
  }
  else{
    return true; // com inimigo
  }
}

bool RightDetection(){
  bool right_IR_read = digitalRead(rightIRpin);
  if (right_IR_read == 0){
    return false; // sem inimigo
  }
  else{
    return true;  // com inimigo
  }
}


#endif