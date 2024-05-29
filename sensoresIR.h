#ifndef sensoresIR_H
#define sensoresIR_H

#define leftIRpin 27
#define rightIRpin 26


bool LeftDetection(){
  float left_IR_read = digitalRead(leftIRpin);
  if (left_IR_read == 1){
    return false; // sem inimigo
  }
  else{
    return true; // com inimigo
  }
}

bool RightDetection(){
  float right_IR_read = digitalRead(rightIRpin);
  if (right_IR_read == 1){
    return false; // sem inimigo
  }
  else{
    return true;  // com inimigo
  }
}


#endif