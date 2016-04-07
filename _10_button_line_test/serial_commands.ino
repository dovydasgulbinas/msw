

void attachCommandCallbacks()// All callbacks must be added here!
{
  cmdMessenger.attach(4, print_num);
  cmdMessenger.attach(OnUnknownCommand);// default command ,ust be placed at the end!
}

void print_num() {// this will completely override the values on the display // show delay,
#if DEBUG
  cmdMessenger.sendCmd(4, "\t@print_num");
#endif
  //The score arragement XX_YY, where XX is ct score, _ is blank segment, YY is t score
  int num = cmdMessenger.readInt16Arg();
  printNumber(num, 0, 0, false);
//
}

void OnUnknownCommand() // Called when a received command has no attached function
{
#if DEBUG
  cmdMessenger.sendCmd(0, "ERROR NO CMD");

#endif
  while (Serial.available()) {
    Serial.read();
  }
}

void initSerial() {
  Serial.begin(115200);
  cmdMessenger.printLfCr(); // Adds newline to every command
  attachCommandCallbacks();
#if DEBUG
  cmdMessenger.sendCmd(0, "Arduino has started!");  //boot message
#endif
}
