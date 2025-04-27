// Get presence sensor data
void getData(sths34pf80_tmos_func_status_t status){
  mySensor.getStatus(&status);
  Serial.println("Data ready! via funct");
}

// Handle interrupt
bool interruptTriggered(){
  if(interruptFlag == true) {
    interruptFlag = false;
    return 1;
  }
  else {
    return 0;
  }
}

bool presenceDetected(sths34pf80_tmos_func_status_t status){
  if(status.pres_flag == 1) {
    return 1;
  }
  else {
    return 0;
  }
}

bool motionDetected(sths34pf80_tmos_func_status_t status){
  if(status.mot_flag == 1) {
    return 1;
  }
  else {
    return 0;
  }
}

bool tAmbShockDetected(sths34pf80_tmos_func_status_t status){
  if(status.tamb_shock_flag == 1) {
    return 1;
  }
  else {
    return 0;
  }
}