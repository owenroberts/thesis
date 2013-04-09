import oscP5.*;
import netP5.*;
import processing.serial.*;
import java.awt.*;
import controlP5.*;
ControlP5 controlP5;

Serial myPort;
OscP5 oscP5;
NetAddress myBroadcastLocation; 

Textfield textField;

String whichBot = "1";

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
  myBroadcastLocation = new NetAddress("127.0.0.1", 8000);

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
    if (whichBot == "1")
      myPort.write("p");
    talktimer = millis();
  }

  textAlign(CENTER, TOP);
  if (whichBot.equals("1")) {
    fill(200, 20, 200);
  } 
  else {
    fill(255);
  }
  rect(5, 5, 25, 25);
  fill(255, 0, 255);
  text("1", 5, 5, 25, 25); 

  if (whichBot.equals("2")) {
    fill(200, 20, 200);
  } 
  else {
    fill(255);
  }
  rect(35, 5, 25, 25);
  fill(255, 0, 255);
  text("2", 35, 5, 25, 25);

  ////front legs forward button
  makeButton("W", 5, 65);
  ///front legs back button
  makeButton("S", 5, 95);
  ///walk slow
  makeButton("E", 35, 65);
  ///walk fast
  makeButton("R", 65, 65);
  ///walk fast 2
  makeButton("T", 95, 65);
  ///back up
  makeButton("D", 35, 95);
  ///back forward
  makeButton("F", 65, 95);
  //spine right
  makeButton("Z", 5, 125);
  //spine left
  makeButton("X", 35, 125);
  ///talk a lot
  makeButton("U", 155, 65);
  ///talk middle
  makeButton("I", 185, 65);
  ///talk short
  makeButton("O", 215, 65);
  ///purr
  makeButton("P", 245, 65);


  textAlign(LEFT, TOP);
  fill(0, 255, 255);
  text(lines[line], 5, 200, width - 5, height - 200);
}

void mousePressed() {
}

void makeButton(String letter, int _x, int _y) {

  fill(255);
  rect(_x, _y, 25, 25);
  fill(255, 0, 255);
  text(letter, _x, _y, 25, 25);
}


void sendEvent(String bot, int eventData) {
  OscMessage oscMsg = new OscMessage("/lines");
  oscMsg.add(whichBot);
  oscMsg.add(eventData);
  oscP5.send(oscMsg, myBroadcastLocation);
}

void keyPressed() {

  if (key == CODED) {
    if (keyCode == RIGHT) {

      if (line < lines.length - 1) {
        line++;
        talktimer = millis();
      }
      String[] m1 = match(lines[line], "0. = ");
      if (m1 != null) {
        String[] m2 = split(m1[0], " ");
        String[] m3 = split(m2[0], "0");
        thisline = lines[line].replace("0" + m3[1]+" = ", "");
        whichBot = m3[1];
        myPort.write(whichBot);
        sendEvent(whichBot, line);
        talk(thisline);
        talk(thisline);
      }
    }

    else if (keyCode == LEFT) {
    }
  }

  else if ( key == '1') {
    whichBot = "1";
    myPort.write(whichBot);
  } 
  else if (key == '2') {
    whichBot = "2";
    myPort.write(whichBot);
  }
  else if (key == 'w') {
    myPort.write('w');
  }
  else if (key == 's') {
    myPort.write('s');
  }
  else if (key == 'e') {
    myPort.write('e');
  }
  else if (key == 'f') {
    myPort.write('f');
  }
  else if (key == 'r') {
    myPort.write('r');
  }
  else if (key == 't') {
    myPort.write('t');
  }
  else if (key == 'z') {
    myPort.write('z');
  }
  else if (key == 'x') {
    myPort.write('x');
  }
  else if (key == 'd') {
    myPort.write('d');
  }
  else if (key == 'f') {
    myPort.write('f');
  }
  else if (key == 'u') {
    myPort.write('u');
  }
  else if (key == 'i') {
    myPort.write('i');
  }
  else if (key == 'o') {
    myPort.write('o');
  }
  else if (key == 'p') {
    myPort.write('p');
  }
}


void talk(String line) {
  if (line.length() < 4) {
    myPort.write("o");
  } 
  else if (line.length()  < 10) {
    println();
    myPort.write("i");
  } 
  else if (line.length() >= 10) {
    myPort.write("u");
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

