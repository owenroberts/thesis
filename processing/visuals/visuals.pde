import oscP5.*;
import netP5.*;


OscP5 oscP5;
NetAddress myRemoteLocation;

PFont myFont;

String whichBot = "1";
String[] lines;
int line;
String thisline1 = "";
String thisline2 = "";

boolean fade1 = false;
boolean fade2 = false;
float fadetime1 = 0;
float fadetime2 = 0;
int alpha1;
int alpha2;
boolean timebool1 = true;
boolean timebool2 = true;
boolean fadedone1 = false;
boolean fadedone2 = false;

float fade = 2000;
int fadein = 15;
int fadeout = 10;
int xm = 50;
int ym = 25;

boolean start = true;

void setup() {
  size(2560, 800);
  frame.removeNotify();
  frame.setUndecorated(true);
  frame.addNotify();

  oscP5 = new OscP5(this, 8000);
  myRemoteLocation = new NetAddress("127.0.0.1", 8000);

  PFont myFont = loadFont("SansSerif-14.vlw");
  textFont(myFont, height/5);
  textAlign(LEFT, TOP);
  textLeading(height/5);

  lines = loadStrings("lines.txt");
}

void draw() {
  if (start) {
    start = false;
    frame.setLocation(1680, 0);
  } 
  background(0);


  if (fade1) {
    if (timebool1) {
      fadetime1 = millis();
      timebool1 = false;
    }
    if (alpha1 < 255 && !fadedone1)
      alpha1+=fadein;
    if (fadetime1 + fade < millis()) {
      if (alpha1 >= 0)
        alpha1-=fadeout;
      fadedone1 = true;
    }
    if (fadedone1 && alpha1 <= 0) {
      fade1 = false;
      timebool1 = true;
      fadedone1 = false;
    }
  }

  if (fade2) {
    if (timebool2) {
      fadetime2 = millis();
      timebool2 = false;
    }
    if (alpha2 < 255 && !fadedone2)
      alpha2+=fadein;
    if (fadetime2 + fade < millis()) {
      if (alpha2 >= 0)
        alpha2-=fadeout;
      fadedone2 = true;
    }
    if (fadedone2 && alpha2 <= 0) {
      fade2 = false;
      timebool2 = true;
      fadedone2 = false;
    }
  }


  String[] m1 = match(lines[line], "0. = ");
  if (m1 != null) {
    if (m1[0].equals("01 = ")) {
      thisline1 = lines[line].replace("01 = ", "");
      if (thisline1.length() <= 5) {
       textSize(height/2);
      } else {
       textSize(height/5);
      } 
      fill(255, alpha1);
      text(thisline1, xm, ym, width/2-2*xm, height - 2*ym);
    } 
    else if (m1[0].equals("02 = ")) {
      thisline2 = lines[line].replace("02 = ", "");
      if (thisline2.length() <= 5) {
       textSize(height/2);
      } else {
       textSize(height/5);
      } 
      fill(255, alpha2);
      text(thisline2, width/2+xm, ym, width/2-2*xm, height - 2*ym);
    }
  }
}

void oscEvent(OscMessage theOscMessage) 
{  
  whichBot = theOscMessage.get(0).stringValue();
  line = theOscMessage.get(1).intValue();

  if (whichBot.equals("1")) {
    fade1 = true;
  } 
  else if (whichBot.equals("2")) {
    fade2 = true;
  }
}
