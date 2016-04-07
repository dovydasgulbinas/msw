//TO DO:
//*Change all of the methods that reference the old _printArray[] and redisign them to take _segment[]
//
//


#include <CmdMessenger.h>  // CmdMessenger
CmdMessenger cmdMessenger = CmdMessenger(Serial);

struct sect_struct {
  uint8_t cState : 5; //Current state // uses HIGH and LOW as an input
  uint8_t pState : 5; //Previous state
} bs[5]; // creating 5 instances of the structure for 5 sectors

#define CELL_CLK (13)
#define CELL_DATA (12)
#define CELL_LT (11)
#define BUTTON_LINE (2)
#define DEBUG 1

long _now = 0, _btn_now = 0, _btn_scan_period = 250;
//TEST VARS
long _sN = 0, _sC = 250;
byte _tcnt = 0; // tick counter tracks what to display on the sector
byte _c = 0;

boolean _disp_test  = true;
//
byte _printArray[5] = {138, 138, 138, 138, 138}; //it the initial value of the array after first push it will be displayed
boolean time_to_trigger( long now, long *lastNow, long callPeriod);

//void printNumber(int n, byte reserved_slots = 2, byte shift_to_left = 1, boolean show_leading_zeroes = true);
void process_int(int n, byte reserved_slots = 0, byte shift_to_left = 0, boolean show_leading_zeroes = false);

void test_sector( byte clk, byte data, byte lt, byte *tick, long now, long *lastNow, long callPeriod);



/// new build
boolean line_is_hot(uint8_t line = BUTTON_LINE);
void arm_sector(byte secId, byte segment[] , byte clk, byte data, byte lt); 


///////////////////not yet used
byte _segment[25] = {
  0, 1, 2, 3, 4,
  2, 3, 4, 5, 6,
  9, 8, 7, 9, 7,
  6, 7, 0, 0, 0,
  8, 9, 8, 9, 1,
};
byte _prev_buttons[25] = {//Stores the last state of the button // JUST TO BE EXPLICIT WHAT STATE THEY ARE NOW
LOW, LOW, LOW, LOW, LOW, 
LOW, LOW, LOW, LOW, LOW, 
LOW, LOW, LOW, LOW, LOW, 
LOW, LOW, LOW, LOW, LOW, 
LOW, LOW, LOW, LOW, LOW,  
}


uint8_t button_click (uint8_t line = BUTTON_LINE, byte segment[] = _segment , byte clk = CELL_CLK, byte data = CELL_DATA , byte lt = CELL_LT );
void arm_segment( byte segment[] = _segment , byte clk = CELL_CLK, byte data = CELL_DATA , byte lt = CELL_LT);
//void arm_sector(); 
void arm_sector(byte t = 9, byte secId = 1 ,byte segment[] = _segment , byte clk = CELL_CLK, byte data = CELL_DATA , byte lt = CELL_LT);
void disarm_sector(byte t = 9, byte secId = 1 ,byte segment[] = _segment , byte clk = CELL_CLK, byte data = CELL_DATA , byte lt = CELL_LT);

void arm_cell(byte t , byte secId , byte cellId, byte segment[] = _segment , byte clk = CELL_CLK, byte data = CELL_DATA , byte lt = CELL_LT);
/////////////////////


void setup() {
  initSerial();
  pinMode(CELL_CLK, OUTPUT);
  pinMode(CELL_DATA, OUTPUT);
  pinMode(CELL_LT, OUTPUT);
  pinMode(BUTTON_LINE, INPUT);
  print_byte_sector("before: ", 1, _segment);
  //arm_cell(0,2,  _segment , CELL_CLK, CELL_DATA, CELL_LT);
  arm_sector(); // must be called for the first time if not no buton presses will be registered
  print_byte_sector("after-arm-bef-dis: ", 1, _segment);
disarm_sector();
  print_byte_sector("after-disarm: ", 1, _segment);

print_byte_sector("before loop:", 1 , _segment);
for(int i = 0; i<5; i++){
Serial.print(i);
Serial.print(".\t");
//arm_cell(9,1,i);
 print_byte_sector("cell arm: ", 1, _segment);  
}
  
  arm_sector();
  
}

void loop() {
  _now = millis();


  if(_disp_test){
  test_sector( CELL_CLK, CELL_DATA, CELL_LT, &_tcnt, _now, &_sN, _sC);
  //for release methods refet to 05_sketch
  }

else{
  if (line_is_hot()) {
    _c++;
    if (_c == 1) {
      delay(100); // will wait for 100 ms after receiving a button press this works a debounce time
      Serial.println("HOT 1");
    }
  }
  else {
    _c = 0;
  }

  if (_c > 1) { // button debounding has stopped and we can check which button has been pressed
    Serial.println("HOT 2");
    Serial.print("BUTTON CODE:\t");
    byte code = button_click();
    arm_sector();
    //arm_segment();
    Serial.println(code, HEX);
  }
} // else

cmdMessenger.feedinSerialData();//must be called always
}//looop








