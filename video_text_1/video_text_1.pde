import processing.video.*;

Capture video;

String[] lines;
char[] letters;
PFont font;
float fontSize = 40;

int rectBorder = 20;
int textBorder = 20;
int rectCornerAngle = 15;

void setup() {
  size(640, 720);

  lines = loadStrings("lines-cat-01.txt");

  video = new Capture(this, 640, 480);
  video.start();  

  //font = loadFont("");
  textSize(fontSize);

  background(0, 0, 0);
  colorMode(HSB, 360, 100, 100);
  fill(270, 20, 100);
  stroke(0, 10, 40);
  strokeWeight(5);
  
}


void captureEvent(Capture c) {
  c.read();
}


void draw() {
  image(video, 0, 0);

  fill(270, 10, 100);
  rect(rectBorder, video.height + rectBorder, width - 2*rectBorder, height - video.height - 2*rectBorder, rectCornerAngle);
  
  
  fill(0);
  String s="Ş";
  text(lines[2], rectBorder + textBorder, video.height + rectBorder + textBorder, width - 2*rectBorder - 2*textBorder, height - video.height - 2*rectBorder - 2*textBorder);
  
  
  
}




void keyPressed() {
  switch (key) {
  case 'g': 
    println("g");
  }
}

