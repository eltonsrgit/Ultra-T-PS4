#ifndef sensoresIR_H
#define sensoresIR_H

#define leftIRpin 33
#define rightIRpin 25

#define JsumoLeft 35
#define JsumoRight 32


bool LeftDetection(){
  bool left_IR_read = digitalRead(leftIRpin);
  if (left_IR_read == 1){
    return false; // sem inimigo
  }
  else{
    return true; // com inimigo
  }
}

bool RightDetection(){
  bool right_IR_read = digitalRead(rightIRpin);
  if (right_IR_read == 1){
    return false; // sem inimigo
  }
  else{
    return true;  // com inimigo
  }
}

bool jsumoLeftDet(){
  bool leftRay = digitalRead(JsumoLeft);
  if (leftRay == 0){
    return false;
  }
  else {
    return true;
  }
}

bool jsumoRightDet(){
  bool rightRay = digitalRead(JsumoRight);
  if (rightRay == 0){
    return false;
  }
  else {
    return true;
  }
}

#endif