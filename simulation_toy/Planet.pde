class Planet {
  //orbiting radius of each planet to the parent
  float radius;
  //orbiting angle
  float angle;
  //distance between the nearest neighbor
  float distance;
  //child planet list 
  Planet[] planets;
  //orbitspeed
  float orbitspeed;
  
  
  Planet(float r, float d, float o){
  radius = r;
  angle = random(TWO_PI);
  distance = d;
  //orbitspeed = random(0.01,0.03);
  orbitspeed = o;
}

  void createplanet(int total, int level) {
    planets = new Planet[total];
    for (int i = 0; i < planets.length; i++){
      float r = radius*0.5;
      float d = random(100,200);
      float o = random(0.02,0.01);
      if (level == 0) {
        d = 300;
        o = 0.01;
      } else {
        d = 50;
        o = 0.05;
      }
      
      planets[i] = new Planet(r,d,o);
      if (level < 1){
        planets[i].createplanet(1, level + 1);
      }
    }
  }
  
  void orbit() {
    angle = angle + orbitspeed; 
    if(planets != null){
      for (int i = 0; i < planets.length; i++) {
        planets[i].orbit();
      }
    }
  }
  
  
  void show() {
    pushMatrix();
    fill(255,100);
    rotate(angle);
    translate(distance,0);
    
    //fill(255);
    ellipse(0, 0, radius*2, radius*2);
    if(planets != null){
      for (int i = 0; i < planets.length; i++) {
        planets[i].show();
      }
    }
    popMatrix();
  }




}
