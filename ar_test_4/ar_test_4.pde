

/*
trying to make ar program with objloader
 finna add new markers, more objects
 */

import saito.objloader.*;


OBJModel btc;
OBJModel cat;
float rotX, rotY;

import processing.video.*;
import jp.nyatla.nyar4psg.*;
Capture cam;
MultiMarker nya;


void setup()
{
  size(640, 480, P3D);
  frameRate(30);
  
  String[] cameras = Capture.list();
  println(cameras);

  //cam = new Capture(this, width, height, "Cisco VT Advantage");
  cam = new Capture(this, width, height);

  nya = new MultiMarker(this, width, height, "camera_para.dat");
  nya.addARMarker("patt.hiro", 80);//id=0
  nya.addARMarker("cat_1.pat", 80);//id=1

  btc = new OBJModel(this, "once.obj", "absolute", TRIANGLES);
  btc.enableDebug();

  btc.scale(1);
  btc.translateToCenter();

  cat = new OBJModel(this, "cat.obj", "absolute", TRIANGLES);
  cat.scale(0.05);
  cat.translateToCenter();

  noStroke();
}

void draw()
{
  if (cam.available() !=true) {
    return;
  }
  background(129);
  lights();

  cam.read();
  nya.detect(cam);
  nya.drawBackground(cam);
   for (int i=0;i<2;i++) {
    if ((!nya.isExistMarker(i))) {
      continue;
    }
    nya.beginTransform(i);
    if (i==0) {
      rotateX(-5);
      translate(0, 50, 10);
      btc.draw();
    } else if (i==1) {
      rotateX(4);
      rotateY(1.3);
      rotateZ(-0.5);
      //println("X:" + rotX +" and Y:" + rotY);
      translate(0, 30, -20);
      cat.draw();
    }
    nya.endTransform();
  }
}

/* USE THIS TO ADJUST ROTATION IF NEEDED
void mouseDragged()
{
    rotX += (mouseX - pmouseX) * 0.01;
    rotY -= (mouseY - pmouseY) * 0.01;
}
*/

