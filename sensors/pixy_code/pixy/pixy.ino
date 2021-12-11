#include <Pixy2.h>

Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  // we need to initialize the pixy object
  pixy.init();
  // Change to line tracking program
  pixy.changeProg("block");
}

void loop()
{
  static int i = 0;
  char buf[128];
 
  uint16_t blocks = pixy.ccc.getBlocks();
  i++;
  // print all blocks
  if (blocks && i % 50 == 0) { // change the frequency of printing 
      int16_t angle = pixy.ccc.blocks[0].m_angle;

      sprintf(buf, "x Center of block: %d\n", pixy.ccc.blocks[0].m_x);
      Serial.print(buf);
      sprintf(buf, "Angle: %d\n", angle);
      Serial.print(buf);

      // prepare data and ship
      byte * data = (byte *) &angle;
      Serial.write(data, sizeof(angle));
  }
}