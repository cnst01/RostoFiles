#include<Servo.h>

struct
{
  Servo x;
  Servo y;
  Servo esq;
  Servo dir;
}face;

void setup() 
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(12, INPUT_PULLUP);
  face.x.attach(5);
  face.y.attach(6);
  face.esq.attach(10);
  face.dir.attach(11);
  face.x.write(30);
  face.y.write(50);
  face.esq.write(15);
  face.dir.write(40);
  delay(10);
}

void blink()
{
  face.esq.write(40);
  face.dir.write(5);
  delay(10);
  face.esq.write(15);
  face.dir.write(40);
  
}

void loop() 
{
  face.x.write(int(90 - (analogRead(A0)/10.24)));
  face.y.write(int(analogRead(A1)/10.24));
  if(digitalRead(12) == 0){
    blink();
  }
}


/*
eixo y dos olhos varia de 40 a 100
eixo x 1 a 60
esq fechado = 1 aberto = 40
dir fechado = 50 aberto = 1

*/