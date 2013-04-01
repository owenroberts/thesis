import oscP5.*;
import netP5.*;
import processing.serial.*;
import java.awt.*;
import controlP5.*;
ControlP5 controlP5;


Serial myPort;
OscP5 oscP5;
NetAddress myRemoteLocation; 

Panel panel1 = new Panel();


Textfield textField;

char whichBot = '0';

int lines = 0;

void setup() {
  size(400, 400);
  println(Serial.list());
  String portname = Serial.list()[0];
  myPort = new Serial(this, portname, 57600);
  controlP5 = new ControlP5(this);

  oscP5 = new OscP5(this, 12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 8000);

  textAlign(CENTER, TOP);

  controlP5.setColorForeground(color(255, 0, 255));
  controlP5.setColorBackground(color(255));
  controlP5.setColorLabel(color(0));
  controlP5.setColorValue(0xffff88ff);
  controlP5.setColorActive(0xffff0000);


  textField = controlP5.addTextfield("enter", 100, 10, 200, 20);
  textField.setSize(200, 40);
}

void draw() {
  background(200);

  if (whichBot == '1') {
    fill(200, 20, 200);
  } 
  else {
    fill(255);
  }
  rect(5, 5, 25, 25);
  fill(255, 0, 255);
  textSize(20);
  text("1", 5, 5, 25, 25); 

  if (whichBot == '2') {
    fill(200, 20, 200);
  } 
  else {
    fill(255);
  }
  rect(35, 5, 25, 25);
  fill(255, 0, 255);
  textSize(20);
  text("2", 35, 5, 25, 25);
}

void sendEvent(String eventData) {
  OscMessage oscMsg = new OscMessage("/unitylines");
  oscMsg.add(eventData);
  oscP5.send(oscMsg, myRemoteLocation);
}

void keyPressed() {
  if (key == CODED) {
    if (keyCode == RIGHT) {
      sendEvent("right");
    } 
    else if (keyCode == LEFT) {
      sendEvent("left");
      println("ufkc");
    }
  } else if( key == '1') {
    whichBot = '1';
    println("whichbot");
  } else if (key == '2') {
    whichBot = '2';
  }

}

public void enter(String theText) {
  
    for (int i = 0; i < theText.length(); i++) {
      myPort.write(theText.charAt(i));
      println(theText.charAt(i));
    }
  }

void mousePressed() {
  if (overButton(5, 5, 25, 25)) {
    whichBot = '1';
    myPort.write(whichBot);
  }
  if (overButton(35, 5, 25, 25)) {
    whichBot = '2';
    myPort.write(whichBot);
  }
}

boolean overButton(int x, int y, int width, int height) 
{
  if (mouseX >= x && mouseX <= x+width && 
    mouseY >= y && mouseY <= y+height) {
    return true;
  } 
  else {
    return false;
  }
}

