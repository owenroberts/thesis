import oscP5.*;
import netP5.*;
import processing.serial.*;
import java.awt.*;
import controlP5.*;
ControlP5 controlP5;

Serial myPort;
OscP5 oscP5;
NetAddress myRemoteLocation; 

Textfield textField;

String whichBot = "0";

String[] lines;
int line;
String thisline = "";
float talktimer = 0;

void setup() {
  size(400, 400);
  println(Serial.list());
  String portname = Serial.list()[0];
  myPort = new Serial(this, portname, 57600);
  controlP5 = new ControlP5(this);

  oscP5 = new OscP5(this, 12000);
  myRemoteLocation = new NetAddress("127.0.0.1", 8000);

  PFont myFont = loadFont("SansSerif-14.vlw");
  textFont(myFont, 14);
  textAlign(CENTER, TOP);
  textSize(20);

  controlP5.setColorForeground(color(255, 0, 255));
  controlP5.setColorBackground(color(255));
  controlP5.setColorLabel(color(0));
  controlP5.setColorValue(0xffff88ff);
  controlP5.setColorActive(0xffff0000);

  textField = controlP5.addTextfield("enter", 100, 10, 200, 20);
  textField.setSize(200, 20);

  lines = loadStrings("lines.txt");


}

void draw() {
  background(50);

  if (talktimer + 50000 < millis()) {
    myPort.write("p");
    talktimer = millis();
  }

  textAlign(CENTER, TOP);
  if (whichBot == "1") {
    fill(200, 20, 200);
  } 
  else {
    fill(255);
  }
  rect(5, 5, 25, 25);
  fill(255, 0, 255);
  text("1", 5, 5, 25, 25); 

  if (whichBot == "2") {
    fill(200, 20, 200);
  } 
  else {
    fill(255);
  }
  rect(35, 5, 25, 25);
  fill(255, 0, 255);
  text("2", 35, 5, 25, 25);

  ///front legs forward button
  fill(255);
  rect(5, 65, 25, 25);
  fill(255, 0, 255);
  text("W", 5, 65, 25, 25);

  ///front legs back button
  fill(255);
  rect(5, 95, 25, 25);
  fill(255, 0, 255);
  text("S", 5, 95, 25, 25);

  ///walk slow
  fill(255);
  rect(35, 65, 25, 25);
  fill(255, 0, 255);
  text("E", 35, 65, 25, 25);

  ///walk fast
  fill(255);
  rect(65, 65, 25, 25);
  fill(255, 0, 255);
  text("R", 65, 65, 25, 25);

  ///walk fast 2
  fill(255);
  rect(95, 65, 25, 25);
  fill(255, 0, 255);
  text("T", 95, 65, 25, 25);

  ///back up
  fill(255);
  rect(35, 95, 25, 25);
  fill(255, 0, 255);
  text("D", 35, 95, 25, 25);

  ///back forward
  fill(255);
  rect(65, 95, 25, 25);
  fill(255, 0, 255);
  text("F", 65, 95, 25, 25);

  //spine right
  fill(255);
  rect(5, 125, 25, 25);
  fill(255, 0, 255);
  text("Z", 5, 125, 25, 25);

  //spine left
  fill(255);
  rect(35, 125, 25, 25);
  fill(255, 0, 255);
  text("X", 35, 125, 25, 25);

  ///talk a lot
  fill(255);
  rect(155, 65, 25, 25);
  fill(255, 0, 255);
  text("U", 155, 65, 25, 25);

  ///talk middle
  fill(255);
  rect(185, 65, 25, 25);
  fill(255, 0, 255);
  text("I", 185, 65, 25, 25);

  ///talk short
  fill(255);
  rect(215, 65, 25, 25);
  fill(255, 0, 255);
  text("O", 215, 65, 25, 25);

  ///purr
  fill(255);
  rect(245, 65, 25, 25);
  fill(255, 0, 255);
  text("P", 245, 65, 25, 25);


  textAlign(LEFT, TOP);
  fill(0, 255, 255);
  text(lines[line], 5, 300, 200, 50);
}

void mousePressed() {
  if (overButton(5, 5, 25, 25)) {
    whichBot = "1";
    myPort.write(whichBot);
  }
  if (overButton(35, 5, 25, 25)) {
    whichBot = "2";
    myPort.write(whichBot);
  }
  if (overButton(5, 65, 25, 25)) {
    myPort.write("w");
  }
  if (overButton(5, 95, 25, 25)) {
    myPort.write("s");
  }
  if (overButton(35, 65, 25, 25)) {
    myPort.write("e");
  }
  if (overButton(65, 95, 25, 25)) {
    myPort.write("r");
  }
  if (overButton(95, 65, 25, 25)) {
    myPort.write("t");
  }
  if (overButton(35, 95, 25, 25)) {
    myPort.write("d");
  }
  if (overButton(65, 95, 25, 25)) {
    myPort.write("f");
    println("f");
  }
  if (overButton(5, 125, 25, 25)) {
    myPort.write("z");
  }
  if (overButton(35, 125, 25, 25)) {
    myPort.write("x");
  }

  if (overButton(155, 65, 25, 25)) {
    myPort.write("u");
    talktimer = millis();
  }
  if (overButton(185, 65, 25, 25)) {
    myPort.write("i");
    talktimer = millis();
  }
  if (overButton(215, 65, 25, 25)) {
    myPort.write("o");
    talktimer = millis();
  }
  if (overButton(245, 65, 25, 25)) {
    myPort.write("p");
    talktimer = millis();
  }
}

void sendEvent(String bot, int eventData) {
  OscMessage oscMsg = new OscMessage("/unitylines");
  oscMsg.add(bot);
  oscMsg.add(eventData);
  oscP5.send(oscMsg, myRemoteLocation);
}

void keyPressed() {

  if (key == CODED) {
    if (keyCode == RIGHT) {
      if (line < lines.length - 1) {
        line++;
        talktimer = millis();
      }
      if (lines[line].contains("01 = ")) {
        thisline = lines[line].replace("01 = ", "");
        whichBot = "1";
        if (thisline.length() < 4) {
          myPort.write("o");
        } 
        else if (thisline.length()  < 10) {
          myPort.write("i");
        } 
        else if (thisline.length() >= 10) {
          myPort.write("u");
        }
        sendEvent(whichBot, line);
      } 
      else if (lines[line].contains("02 = ")) {
        thisline = lines[line].replace("02 = ", "");
        whichBot = "2";
        sendEvent(whichBot, line);
      }
    } 
    else if (keyCode == LEFT) {
      if (line > 0) {
        line--;
      } 
      if (lines[line].contains("01 = ")) {
        thisline = lines[line].replace("01 = ", "");
        whichBot = "1";
        sendEvent(whichBot, line);
      } 
      else if (lines[line].contains("02 = ")) {
        thisline = lines[line].replace("02 = ", "");
        whichBot = "2";        
        sendEvent(whichBot, line);
      }
    }
  } 
  else if ( key == '1') {
    whichBot = "1";
  } 
  else if (key == '2') {
    whichBot = "2";
  }
}

public void enter(String theText) {

  for (int i = 0; i < theText.length(); i++) {
    myPort.write(theText.charAt(i));
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

