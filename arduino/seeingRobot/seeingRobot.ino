#include <SPI.h>
#include <Pixy.h>
#include <Servo.h> 

Pixy pixy;
Servo left, right;
static int leftCentre = 75;
static int rightCentre = 75;
static int centreZone = 50;
static int delta = 10;
static int idealWidth = 150;
static int minWidth = 50;
static int widthHysterisis = 20;

void setup() {
  Serial.begin(9600);
  Serial.print("Basebot says hello!\n");
  left.attach(5);
  right.attach(6);
}

void loop() {
  // Look for the single largest signature, if found.
  int blocks = pixy.getBlocks();
  delay(30);
  if (blocks) {
    int x = pixy.blocks[0].x-160;
    int width = pixy.blocks[0].width;
    left.attach(5);
    right.attach(6);
    if (width > minWidth) {
      Serial.print(x);
      Serial.print("  ");
      if (x > centreZone) {
        turnRight();
      }
      else if (x < -centreZone) {
        turnLeft();
      }
      else {
        if (width < idealWidth - widthHysterisis) {
          forward();
        } 
        else if (width > idealWidth + widthHysterisis) {
          back();
        } 
        else {
          stop();
        }
      }

    }
    Serial.println(x);
  }
  else {
   stop();
  }

}

void forward() {
  Serial.println("Forwards");
  right.write(rightCentre - delta);
  left.write(leftCentre + delta);
}
void back() {
  Serial.println("Run away!");
  right.write(rightCentre + delta);
  left.write(leftCentre - delta);
}
void turnLeft() {
  Serial.println("Left!");
  left.write(leftCentre - delta);
  right.write(rightCentre - delta);
}
void turnRight() {
  Serial.println("Right!");
  right.write(rightCentre + delta);
  left.write(leftCentre + delta);
}
void stop() {
  Serial.println("Stop");
  right.write(rightCentre);
  left.write(leftCentre);
}















