Planet sun;



void setup(){
  size(1000,1000);
  sun = new Planet(50, 0, 0);
  sun.createplanet(1, 0);
}


void draw() {
  background(0);
  translate(width/2, height/2);
  sun.show();
  sun.orbit();
}
