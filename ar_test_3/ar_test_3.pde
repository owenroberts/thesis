/*
trying to make ar program with objloader
finna add new markers, more objects
 */

import saito.objloader.*;

OBJModel model;
float rotX, rotY;

import processing.video.*;
import jp.nyatla.nyar4psg.*;
Capture cam;
SingleARTKMarker nya;


void setup()
{
  size(800, 600, P3D);
  frameRate(30);

  cam = new Capture(this, width, height);
  nya = new SingleARTKMarker(this, width, height, "camera_para.dat");
  nya.setARCodes("patt.hiro", 80);

  model = new OBJModel(this, "btc.obj", "absolute", TRIANGLES);
  model.enableDebug();

  model.scale(3);
  model.translateToCenter();
  
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
  nya.drawBackground(cam);
  switch(nya.detect(cam)){
  case SingleARTKMarker.ST_NOMARKER:
    return;
  case SingleARTKMarker.ST_NEWMARKER:
    println("Marker found.");
    return;
  case SingleARTKMarker.ST_UPDATEMARKER:
    break;
  case SingleARTKMarker.ST_REMOVEMARKER:
    println("Marker removed.");
    return;
  default:
    return;
  }
  
  nya.beginTransform();//マーカ座標系に設定
  {
    setMatrix(nya.getMarkerMatrix());//マーカ姿勢をセット
    rotateX(-5);
    translate(0,50,10);

    model.draw();
  }
  nya.endTransform();  //マーカ座標系を終了
  
}

