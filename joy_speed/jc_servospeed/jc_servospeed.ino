#import <Servo.h>

struct{
  int x = 512;
  int y = 512;
  int but = 0;
  int last_but = 0;
  int last_x = 512;
  int last_y = 512;
  
}joy;

#define VRX A1
#define VRY A0
#define Button A5

void setup_joy(){
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(Button, INPUT_PULLUP);
}
void joy_refresh(){
  joy.last_x = joy.x;
  joy.last_y = joy.y;
  joy.last_but = joy.but;
  joy.x = int(analogRead(VRX)/10);
  joy.y = int(analogRead(VRY)/10);
  joy.but = digitalRead(Button);
}
int joy_has_changes(int x_offset, int y_offset){
  int diff = joy.x-joy.last_x;
  if(diff > x_offset || diff < x_offset*-1){
    return 1;
  }
  diff = joy.y-joy.last_y;
  if(diff > y_offset || diff < y_offset*-1){
    return 1;
  }
  if(joy.but != joy.last_but){
    return 1;
  }
  return 0;
}

struct{
  Servo EyeX;
  Servo EyeY;
  Servo EsqLid;
  Servo DirLid;
  Servo EsqEyeBrown;
}face;

void setup_face() {
  // put your setup code here, to run once:
  face.EyeX.attach(5);
  face.EyeY.attach(6);
  face.EsqLid.attach(10);
  face.DirLid.attach(11);
  Serial.begin(9600);
  face.EyeX.write(30);
  face.EyeY.write(50);
  face.EsqLid.write(15);
  face.DirLid.write(40);
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
  face.EyeX.write(30);
  face.EyeY.write(50);
  face.EsqLid.write(15);
  face.DirLid.write(40);
}
void blink(){
  Serial.println("2 eyes blinking");
  face.EsqLid.write(40);
  face.DirLid.write(1);
  delay(100);
  move_to_default(); 
}
void move_eyes(int x,int y){
  face.EyeX.write(0.6*x);
  face.EyeY.write((0.6*y) + 40);
}
void move_eyes_S(int x, int y, int speed){
  write_speed(face.EyeX,int(0.6*x), speed);
  write_speed(face.EyeX,int((0.6*x)+40), speed);
}

/*
eixo y dos olhos varia de 40 a 100
eixo x 1 a 60
esq fechado = 1 aberto = 40
dir fechado = 50 aberto = 1

*/


void Face_control(){
  int speed = 60;
  joy_refresh();
  if(joy_has_changes(1,1)){
    Serial.print("X: ");
    Serial.print(joy.x);
    Serial.print(" | Y: ");
    Serial.println(joy.y);
    Serial.print("Button: ");
    Serial.println(joy.but);
    move_eyes_S(joy.x, joy.y, speed);
    if(!joy.but){
      blink();
    }
  }
}
void testing_joy(){
  joy_refresh();
  if(joy_has_changes(10, 10)){
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
  setup_joy();
  setup_face();
}

void loop() {
  Face_control();    
}
