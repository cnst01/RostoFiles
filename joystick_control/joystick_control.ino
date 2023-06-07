

struct {
  #define VRX A1
  #define VRY A0
  #define Button A5
  int x = 512;
  int y = 512;
  int but = 0;
  int last_but = 0;
  int last_x = 512;
  int last_y = 512;
  void refresh(){
    last_x = x;
    last_y = y;
    last_but = but;
    x = analogRead(VRX);
    y = analogRead(VRY);
    but = digitalRead(Button);
  }
  void setup(){
    pinMode(VRX, INPUT);
    pinMode(VRY, INPUT);
    pinMode(Button, INPUT_PULLUP);
  }
  int has_changes(int x_offset, int y_offset){
    int diff = x-last_x;
    if(diff > x_offset || diff < x_offset*-1){
      return 1;
    }
    diff = y-last_y;
    if(diff > y_offset || diff < y_offset*-1){
      return 1;
    }
    if(but != last_but){
      return 1;
    }
    return 0;
  }
} joy;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  joy.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  joy.refresh();
  if(joy.has_changes(10, 10) == 1){
    Serial.print("X: ");
    Serial.print(joy.x);
    Serial.print(" | Y: ");
    Serial.println(joy.y);
    Serial.print("Button: ");
    Serial.println(joy.but);
  }
  
  


}
