#import <Servo.h>

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
  void setup(){
    pinMode(VRX, INPUT);
    pinMode(VRY, INPUT);
    pinMode(Button, INPUT_PULLUP);
  }
  void refresh(){
    last_x = x;
    last_y = y;
    last_but = but;
    x = int(analogRead(VRX)*100/1024);
    y = int(analogRead(VRY)*100/1024);
    but = digitalRead(Button);
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

struct{
  Servo EyeX;
  Servo EyeY;
  Servo EsqLid;
  Servo DirLid;
  Servo EsqEyeBrown;
  void setup() {
    // put your setup code here, to run once:
    EyeX.attach(3);
    EyeY.attach(4);
    EsqLid.attach(8);
    DirLid.attach(11);
    Serial.begin(9600);
    EyeX.write(30);
    EyeY.write(50);
    EsqLid.write(15);
    DirLid.write(40);
  }
  void write_speed(Servo motor, int pos, int speed){// speed = degrees per second
    int p = int(1000/speed);
    int i = motor.read();
    if (i > pos)
    {
      for(i; i>pos; i--){
        motor.write(i);
        delay(p);
      }
    }
    else if (i < pos)
    {
      for(i; i<pos; i++){
        motor.write(i);
        delay(p);
      }
    }
  }
  void move_to_default(){
    EyeX.write(30);
    EyeY.write(50);
    EsqLid.write(15);
    DirLid.write(40);
  }
  void blink(){
    Serial.println("2 eyes blinking");
    EsqLid.write(40);
    DirLid.write(1);
    delay(100);
    move_to_default(); 
  }
  void move_eyes(int x,int y){
    EyeX.write(0.6*x);
    EyeY.write((0.6*y) + 40);
  }
  void move_eyes_S(int x, int y, int speed){
    write_speed(EyeX,int(0.6*x), speed);
    write_speed(EyeX,int((0.6*x)+40), speed);
  }
}face;

/*
eixo y dos olhos varia de 40 a 100
eixo x 1 a 60
esq fechado = 1 aberto = 40
dir fechado = 50 aberto = 1

*/


void Face_control(){
  int speed = 20;
  joy.refresh();
  if(joy.has_changes(10,10)){
    face.move_eyes_S(joy.x, joy.y, speed);
    if(!joy.but){
      face.blink();
    }
  }
}
void testing_joy(){
  // put your main code here, to run repeatedly:
  joy.refresh();
  if(joy.has_changes(10, 10)){
    Serial.print("X: ");
    Serial.print(joy.x);
    Serial.print(" | Y: ");
    Serial.println(joy.y);
    Serial.print("Button: ");
    Serial.println(joy.but);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  joy.setup();
  face.setup();
}

void loop() {
  Face_control();    
}